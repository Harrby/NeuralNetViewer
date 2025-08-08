
#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(NeuralNetOptionsData& network_parameters,  QObject* parent)
    : QObject(parent),
    m_network_parameters(network_parameters),
    m_loss_function(get_loss_function(network_parameters.getLossFunction())),
    m_optimiser(get_optimiser_function(network_parameters.getOptimiser()))
{

}

void NeuralNetwork::initialise_network(){
    m_layers.clear();
    m_activation_functions.clear();

    for (int i=0; i < m_network_parameters.getLenLayers(); i++){
        int input_size = (i == 0) ? m_network_parameters.getInputSize() : m_network_parameters.getLayerData(i-1).neurons;
        if (i==m_network_parameters.getLenLayers()-1){
            m_network_parameters.setLayerNeurons(i, 10);
        }

        m_layers.push_back(
            std::make_unique<Layer>(input_size, m_network_parameters.getLayerData(i))
            );



        m_activation_functions.push_back(
            get_activation(m_network_parameters.getLayerActivationFunction(i))
            );
    }
}



void NeuralNetwork::train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels){
    qDebug() << "inputs.rows() =" << inputs.rows();
    qDebug() << "labels.size() =" << labels.size();
    int num_samples = inputs.rows();
    std::vector<int> perm(num_samples);
    std::iota(perm.begin(), perm.end(), 0);           // 0,1,2,…,N-1

    if (m_network_parameters.isShuffleEnabled()) {
        static thread_local std::mt19937 rng{std::random_device{}()};
        std::shuffle(perm.begin(), perm.end(), rng);
    }

    const bool use_val = m_network_parameters.isValidationEnabled();
    float split        = m_network_parameters.getValidationSplit();

    int val_sz   = use_val ? static_cast<int>(split * num_samples) : 0;
    int train_sz = num_samples - val_sz;

    Eigen::MatrixXf X_train(train_sz, inputs.cols());
    Eigen::VectorXi y_train(train_sz);
    Eigen::MatrixXf X_val(val_sz,   inputs.cols());
    Eigen::VectorXi y_val(val_sz);

    for (int k = 0; k < val_sz; ++k) {
        int idx = perm[k];
        X_val.row(k) = inputs.row(idx);
        y_val(k)     = labels(idx);
    }
    qDebug() << "x val size" << X_val.size();
    qDebug() << "y val size" << y_val.size();
    qDebug() << "x vals rows" << X_val.rows();
    for (int k = 0; k < train_sz; ++k) {
        int idx = perm[val_sz + k];
        X_train.row(k) = inputs.row(idx);
        y_train(k)     = labels(idx);
    }

    const Eigen::MatrixXf& train_X = use_val ? X_train : inputs;
    const Eigen::VectorXi& train_y = use_val ? y_train : labels;

    num_samples = train_X.rows();

    int batch_size = m_network_parameters.getBatchSize();
    float lr = m_network_parameters.getLearningRate();

    for (int epoch=0; epoch < m_network_parameters.getEpochs(); ++epoch){
        qDebug() << "epoch:" << epoch;
        int total_training_correct = 0;
        float total_training_loss = 0.0f;
        float total_training_seen = 0.0f;

        int num_batches   = 0;
        for (int i=0; i<num_samples; i += batch_size){
            if (isCancelled()){
                return;
            }

            int actual_batch_size = std::min(batch_size, num_samples - i);
            for (std::unique_ptr<Layer>& layer : m_layers){
                layer->zeroGradients();
            }
            int correct_preds = 0;
            float batch_training_loss = 0.0f;

            // x is shape (batch_size, input_size)
            Eigen::MatrixXf x = train_X.block(i, 0, actual_batch_size, m_network_parameters.getInputSize());

            // forward pass
            for (int layer=0; layer < m_network_parameters.getLenLayers(); ++layer){
                x = m_layers.at(layer)->forward(x);
                x = m_activation_functions.at(layer)->forward(x);
            }

            Eigen::VectorXi true_classes = train_y.segment(i, actual_batch_size);
            Eigen::VectorXf batch_losses =  m_loss_function.forward(x, true_classes);






            for (int j=0; j < actual_batch_size; ++j){
                Eigen::VectorXf x = train_X.row(i+j).transpose();

                // forward pass
                for (int layer=0; layer < m_network_parameters.getLenLayers(); ++layer){
                    x = m_layers.at(layer)->forward(x);
                    x = m_activation_functions.at(layer)->forward(x);
                }
                int true_class = train_y(i + j);
                float loss = m_loss_function.forward(x, true_class);
                batch_training_loss += loss;

                //Accuracy
                Eigen::Index predicted_class;
                x.maxCoeff(&predicted_class);
                if (predicted_class == true_class)
                    ++correct_preds;


                Eigen::VectorXf gradients = m_loss_function.backward(x, true_class);
                for (int l=m_network_parameters.getLenLayers()-1; l >= 0; --l){
                    constexpr bool Accumulate = true;
                    gradients = m_activation_functions.at(l)->backward(gradients);
                    gradients = m_layers.at(l)->backward(gradients, Accumulate);

                }




            }

            ++num_batches;

            batch_training_loss /= actual_batch_size;
            total_training_loss += batch_training_loss;
            total_training_seen += actual_batch_size;

            total_training_correct += correct_preds;

            for (std::unique_ptr<Layer>& layer: m_layers){
                layer->scaleGradients(1.0f / actual_batch_size);
            }

            for (std::unique_ptr<Layer>& layer: m_layers){
                m_optimiser.update(layer->getWeights(), layer->getWeightGradients(), lr);
                m_optimiser.update(layer->getBiases(), layer->getBiasGradients(), lr);
            }


        }
        Metrics val_metrics;
        if (use_val){
            val_metrics = validate(X_val, y_val);
        } else{
            val_metrics = {0.f, 0.f};
        }


        qDebug() << "num batches: " << num_batches;
        qDebug() << "total training seen" << total_training_seen;
        float avg_training_loss = total_training_loss / num_batches;
        float avg_training_accuracy = static_cast<float>(total_training_correct) / total_training_seen;


        EpochStats stats{epoch,  m_network_parameters.getEpochs(), avg_training_loss, val_metrics.loss, avg_training_accuracy, val_metrics.accuracy, 0.0f};

        qDebug() << stats;

        emit epochDataChanged(stats);

    }
}

int NeuralNetwork::predict(const Eigen::VectorXf& inputs){
    Eigen::VectorXf activation = inputs;
    for (int layer=0; layer < m_network_parameters.getLenLayers(); ++layer){

        activation = m_layers.at(layer)->forward(activation);
    }

    Eigen::VectorXf::Index max_index;
    activation.maxCoeff(&max_index);
    return static_cast<int>(max_index);

}




Metrics NeuralNetwork::validate(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels) const{
    Metrics m{0.f, 0.f};
    int correct = 0;

    qDebug() << "inputs.rows()" << inputs.rows();
    qDebug() << "labels.rows()" << labels.rows();

    for (int n = 0; n < inputs.rows(); ++n) {
        Eigen::VectorXf x = inputs.row(n);
        for (int i=0; i < m_network_parameters.getLenLayers(); i++) {
            x = m_layers[i]->forward(x);
            x = m_activation_functions[i]->forward(x);
            // pass is inference-mode safe
        }
        m.loss += m_loss_function.forward(x, labels(n));

        Eigen::Index pred;
        x.maxCoeff(&pred);
        if (pred == labels(n)) ++correct;
    }
    m.loss /= inputs.rows();
    m.accuracy = static_cast<float>(correct) / static_cast<float>(inputs.rows());
    return m;
}

void NeuralNetwork::requestCancel() {
    m_cancel_requested.store(true);
}

bool NeuralNetwork::isCancelled() const {
    return m_cancel_requested.load();
}

void NeuralNetwork::resetCancel() {
    m_cancel_requested.store(false);
}

