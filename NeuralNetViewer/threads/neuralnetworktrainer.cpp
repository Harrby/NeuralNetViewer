
#include "neuralnetworktrainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(NeuralNetwork* neural_network, const Eigen::MatrixXf& features,
                                           const Eigen::VectorXi& labels)
    : QObject{},
    m_nn(neural_network),
    m_features(features),
    m_labels(labels)

{

}

void NeuralNetworkTrainer::run(){
    m_nn->resetCancel();
    m_nn->initialise_network();
    m_nn->train(m_features, m_labels);
    emit finished();
}


