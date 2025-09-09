
#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(NeuralNetOptionsData& network_parameters,  QObject* parent)
    : QObject(parent),
    m_network_parameters(network_parameters),
    m_loss_function(get_loss_function(network_parameters.getLossFunction())),
    m_optimiser(get_optimiser_function(network_parameters.getOptimiser(), network_parameters.getLearningRate(),
                                       network_parameters.getMomentum(), network_parameters.getBeta1(), network_parameters.getBeta2(),
                                       network_parameters.getEpsilon()))
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

        m_dropout_layers.push_back(
            std::make_unique<Dropout>(m_network_parameters.getLayerDropoutRate(i))
            );

        m_optimiser = get_optimiser_function(m_network_parameters.getOptimiser(), m_network_parameters.getLearningRate(),
                                       m_network_parameters.getMomentum(), m_network_parameters.getBeta1(),
                                       m_network_parameters.getBeta2(), m_network_parameters.getEpsilon());

        qDebug() << "layer" << i <<"has dropout rate of" << m_network_parameters.getLayerDropoutRate(i);

    }

}



void NeuralNetwork::train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels){
    qDebug() << "inputs.rows() =" << inputs.rows();
    qDebug() << "labels.size() =" << labels.size();
    std::chrono::duration<double> elapsed{0};
    bool is_training = true;
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
        auto start  = std::chrono::high_resolution_clock::now();
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

            //qDebug() << "network initialised as:" << m_layers[0]->getWeights().rows() << m_layers[1]->getWeights().rows();

            // x is shape (batch_size, input_size)
            Eigen::MatrixXf x = train_X.block(i, 0, actual_batch_size, m_network_parameters.getInputSize());
            Eigen::VectorXi true_classes = train_y.segment(i, actual_batch_size);
            // forward pass + loss +correct_preds calculation
            //qDebug() << "x size is" << x.rows() << x.cols();

            auto result = forward(x, true_classes, is_training);
            Metrics training_metrics = result.first;
            x = result.second;


            total_training_seen += actual_batch_size;
            total_training_correct += training_metrics.correct;
            total_training_loss += training_metrics.loss;

            // backward pass
            Eigen::MatrixXf gradients = m_loss_function.backward(x, true_classes);
            for (int layer=m_network_parameters.getLenLayers()-1; layer >= 0; --layer){
                constexpr bool Accumulate = true;
                gradients = m_activation_functions.at(layer)->backward(gradients);
                gradients = m_layers.at(layer)->backward(gradients, Accumulate);
            }

            ++num_batches;

            for (std::unique_ptr<Layer>& layer: m_layers){
                layer->scaleGradients(1.0f / actual_batch_size);
            }

            for (std::unique_ptr<Layer>& layer: m_layers){
                OptimiserParams params = OptimiserParams{m_network_parameters.getLearningRate(),
                                                         m_network_parameters.getMomentum(), m_network_parameters.getBeta1(),
                                                         m_network_parameters.getBeta2(), m_network_parameters.getEpsilon()};

                m_optimiser->setParams(params);
                m_optimiser->update(layer->getWeights(), layer->getWeightGradients());
                m_optimiser->update(layer->getBiases(), layer->getBiasGradients());
            }


        }
        Metrics val_metrics;
        if (use_val){
            val_metrics = forward(X_val, y_val).first;

        } else{
            val_metrics = {0.f, 0};
        }


        //qDebug() << "num batches: " << num_batches;
        //qDebug() << "total training seen" << total_training_seen;
        float avg_training_loss = total_training_loss / num_batches;
        float avg_training_accuracy = static_cast<float>(total_training_correct) / total_training_seen;
        float validation_accuracy = static_cast<float>(val_metrics.correct) / X_val.rows();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_epoch = end - start;
        elapsed += elapsed_epoch;
        double avg_epoch_time = elapsed.count() / (epoch+1);
        int remaining  = m_network_parameters.getEpochs() - (epoch+1);
        float eta = avg_epoch_time * remaining;




        EpochStats stats{epoch+1,  m_network_parameters.getEpochs(), avg_training_loss, val_metrics.loss, avg_training_accuracy, validation_accuracy, eta};

        qDebug() << stats;

        emit epochDataChanged(stats);

    }
}

int NeuralNetwork::predict(const Eigen::VectorXf& inputs){
    qDebug() << "input is" << inputs.rows() << inputs.cols();
    Eigen::RowVectorXf x = inputs.transpose();
    qDebug() << "x is" << x.rows() << x.cols();
    for (int layer=0; layer < m_network_parameters.getLenLayers(); ++layer){
        x = m_layers.at(layer)->forward(x);
        x = m_activation_functions.at(layer)->forward(x);
    }

    qDebug() << "x shape is" << x.rows() << x.cols();

    Eigen::VectorXf::Index predicted_class;
    x.maxCoeff(&predicted_class);

    qDebug() <<" predicted class is" << predicted_class;



    Softmax softmax = Softmax();
    x = softmax.forward(x);
    Eigen::VectorXf probabilities = x;
    float confidence = x[predicted_class];
    qDebug() << "confidence is " << confidence;

    float entropy = 0.0f;
    for (int i=0; i<x.size(); ++i){
        if(x[i]>0.0f){
            entropy -= x[i]*std::log(x[i]);
        }
    }
    float normalised_entropy = entropy / std::log(x.size());

    // predicted class is target class
    Eigen::VectorXf grad_output = Eigen::VectorXf::Zero(x.size());
    grad_output[predicted_class] = 1.0f;

    Eigen::VectorXf saliency;

    for (int layer=m_network_parameters.getLenLayers()-1; layer >= 0; layer--){
        x = m_activation_functions.at(layer)->backward(x);
        x = m_layers.at(layer)->backward(x, /*accumulate*/ false);
    }
    saliency = x;

    PredictionResults prediction_results{static_cast<int>(predicted_class), confidence, normalised_entropy, probabilities, saliency};
    qDebug() << static_cast<int>(predicted_class) << confidence << normalised_entropy ;

    emit predictionFinished(prediction_results);

    return static_cast<int>(predicted_class);

}




std::pair<Metrics, Eigen::MatrixXf> NeuralNetwork::forward(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels, bool training) const{
    Metrics m{0.f, 0};
    int correct = 0;

    //qDebug() << "inputs.rows()" << inputs.rows();
    //qDebug() << "labels.rows()" << labels.rows();
    Eigen::MatrixXf x = inputs;
    for (int layer=0; layer < m_network_parameters.getLenLayers(); ++layer) {
        x = m_layers[layer]->forward(x);
        x = m_activation_functions[layer]->forward(x);
        x = m_dropout_layers[layer]->apply(x, training);
        // pass is inference-mode safe
    }
    Eigen::VectorXf batch_losses = m_loss_function.forward(x, labels);
    m.loss = batch_losses.sum() / inputs.rows();
    for (int i=0; i < inputs.rows(); ++i){
        Eigen::Index predicted_class;
        Eigen::VectorXf row =  x.row(i);
        row.maxCoeff(&predicted_class);

        if (predicted_class == labels(i)){
            ++correct;
        }



    }
    m.correct = correct;
    return {m, x};
}

void NeuralNetwork::test(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels) {
    const int input_rows = inputs.rows();
    const int batch_size = 1000;
    const int total_batches = (input_rows + batch_size - 1) / batch_size;

    Metrics m{0.f, 0};
    int total_correct = 0;
    float total_loss = 0.f;

    QElapsedTimer timer;
    timer.start();

    for (int b = 0; b < total_batches; ++b) {
        if (isCancelled()){
            return;
        }
        const int start_idx = b * batch_size;
        const int end_idx = std::min(start_idx + batch_size, input_rows);
        const int current_batch_size = end_idx - start_idx;

        // Slice inputs and labels for this batch
        Eigen::MatrixXf x = inputs.middleRows(start_idx, current_batch_size);
        Eigen::VectorXi y = labels.segment(start_idx, current_batch_size);

        // Forward pass through all layers
        for (int layer = 0; layer < m_network_parameters.getLenLayers(); ++layer) {
            x = m_layers[layer]->forward(x);
            x = m_activation_functions[layer]->forward(x);
        }

        // Compute losses
        Eigen::VectorXf batch_losses = m_loss_function.forward(x, y);
        float batch_loss = batch_losses.sum() / current_batch_size;
        total_loss += batch_loss * current_batch_size;

        // Evaluate predictions
        int batch_correct = 0;
        QVector<SampleLogMessageStats> samples_stats;
        samples_stats.reserve(current_batch_size);

        for (int i = 0; i < current_batch_size; ++i) {
            Eigen::Index predicted_class;
            Eigen::VectorXf row = x.row(i);
            row.maxCoeff(&predicted_class);

            if (predicted_class == y(i)) {
                ++batch_correct;
            }

            SampleLogMessageStats sample_stats {
                (start_idx + i),
                static_cast<int>(predicted_class),
                y(i)

            };

            samples_stats.push_back(sample_stats);
        }

        total_correct += batch_correct;

        // Compute cumulative averages
        float avg_loss = total_loss / float(end_idx);
        float avg_accuracy = float(total_correct) / float(end_idx);

        // ETA estimation
        qint64 elapsed_ms = timer.elapsed();
        float avg_time_per_batch = float(elapsed_ms) / float(b + 1);
        float eta = (total_batches - (b + 1)) * avg_time_per_batch / 1000.0f; // seconds


        qDebug() << "after testing, log stats is" << samples_stats.size();


        TestStatusStats status {
            end_idx,
            input_rows,
            eta
        };

        TestOutputStats stats {
            avg_accuracy,
            avg_loss,
            samples_stats
        };

        TestingBatchResults results {
            stats,
            status
        };


        // Example debug output (can remove later)
        qDebug() << "Batch" << (b + 1) << "/" << total_batches
                 << "Cumulative loss:" << avg_loss
                 << "Cumulative accuracy:" << avg_accuracy
                 << "ETA (s):" << status.eta;

        emit batchSamplesFinished(results);

    }
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

