
#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(NeuralNetOptionsData& network_parameters)
    : m_network_parameters(network_parameters),
    m_loss_function(get_loss_function(network_parameters.getLossFunction()))
{

}

void NeuralNetwork::initialise_layers(){
    for (int i=0; i < m_network_parameters.getLenLayers(); i++){
        m_layers.push_back(std::make_unique<Layer>(i, m_network_parameters.getLayerData(i)));
    }

}

void NeuralNetwork::train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels){

    int num_samples = inputs.rows();
    for (int epoch=0; epoch < m_network_parameters.getEpochs(); ++epoch){
        for (int i=0; i<num_samples; i += m_network_parameters.getBatchSize()){
            int actual_batch_size = std::min(m_network_parameters.getBatchSize(), num_samples - i);

            for (int j=0; j < actual_batch_size; ++j){
                Eigen::VectorXf activation = inputs.row(i+j);

                for (int layer=0; layer < m_network_parameters.getLenLayers(); ++layer){
                    activation = m_layers.at(layer)->forward(activation);
                }

                int true_class = labels(i + j);
                float loss = m_loss_function.forward(activation, true_class);

                Eigen::VectorXf gradients = m_loss_function.backward(activation, true_class);

                for (int layer=0; layer < m_network_parameters.getLenLayers(); ++layer){
                    activation = m_layers.at(layer)->backward(gradients);
                }

            }

        }






    }

}

