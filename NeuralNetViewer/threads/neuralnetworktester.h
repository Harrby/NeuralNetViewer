
#ifndef NEURALNETWORKTESTER_H
#define NEURALNETWORKTESTER_H


#include <QObject>
#include "neuralnetwork.h"


class NeuralNetworkTester : public QObject
{
    Q_OBJECT
public:
    NeuralNetworkTester(NeuralNetwork* neural_network, const Eigen::MatrixXf& features, const Eigen::VectorXi& labels);

public slots:
    void run();

signals:
    void finished();

private:
    NeuralNetwork* m_nn;
    Eigen::MatrixXf m_features;
    Eigen::VectorXi m_labels;

};

#endif // NEURALNETWORKTESTER_H
