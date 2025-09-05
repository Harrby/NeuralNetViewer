
#include "neuralnetworktester.h"

NeuralNetworkTester::NeuralNetworkTester(NeuralNetwork* neural_network, const Eigen::MatrixXf& features,
                                           const Eigen::VectorXi& labels)
    : QObject{},
    m_nn(neural_network),
    m_features(features),
    m_labels(labels)

{

}

void NeuralNetworkTester::run(){
    m_nn->resetCancel();
    m_nn->test(m_features, m_labels);
    emit finished();
}


