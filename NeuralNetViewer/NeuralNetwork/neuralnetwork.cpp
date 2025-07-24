
#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(NeuralNetOptionsData& network_parameters)
    : m_network_parameters(network_parameters),
    m_loss_function(get_loss_function(network_parameters.getLossFunction())),
    m_optimiser(get_optimiser_function(network_parameters.getOptimiser()))
{

}

void NeuralNetwork::initialise_layers(){
    for (int i=0; i < m_network_parameters.getLenLayers(); i++){
        m_layers.push_back(std::make_unique<Layer>(i, m_network_parameters.getLayerData(i)));
    }

}

void NeuralNetwork::train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels){
    int num_samples = inputs.rows();
    int batch_size = m_network_parameters.getBatchSize();
    float lr = m_network_parameters.getLearningRate();

    for (int epoch=0; epoch < m_network_parameters.getEpochs(); ++epoch){
        for (int i=0; i<num_samples; i += batch_size){
            int actual_batch_size = std::min(batch_size, num_samples - i);

            for (std::unique_ptr<Layer>& layer : m_layers){
                layer->zeroGradients();
            }


            for (int j=0; j < actual_batch_size; ++j){
                Eigen::VectorXf activation = inputs.row(i+j);

                for (int layer=0; layer < m_network_parameters.getLenLayers(); ++layer){
                    activation = m_layers.at(layer)->forward(activation);
                }

                int true_class = labels(i + j);
                float loss = m_loss_function.forward(activation, true_class);

                Eigen::VectorXf gradients = m_loss_function.backward(activation, true_class);
                for (int l=m_network_parameters.getLenLayers()-1; l >= 0; --l){
                    constexpr bool Accumulate = true;
                    gradients = m_layers.at(l)->backward(gradients, Accumulate);
                }
            }

            for (std::unique_ptr<Layer>& layer: m_layers){
                layer->scaleGradients(1.0f / actual_batch_size);
            }

            for (std::unique_ptr<Layer>& layer: m_layers){
                m_optimiser.update(layer->getWeights(), layer->getWeightGradients(), lr);
                m_optimiser.update(layer->getBiases(), layer->getBiasGradients(), lr);
            }
        }
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

