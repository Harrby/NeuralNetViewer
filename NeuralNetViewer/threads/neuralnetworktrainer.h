
#ifndef NEURALNETWORKTRAINER_H
#define NEURALNETWORKTRAINER_H


#include <QObject>
#include "neuralnetwork.h"

class NeuralNetworkTrainer : public QObject
{
    Q_OBJECT
public:
    NeuralNetworkTrainer(NeuralNetwork* neural_network, const Eigen::MatrixXf& features,
                                  const Eigen::VectorXi& labels);

public slots:
    void run();

signals:
    void finished();

private:
    NeuralNetwork* m_nn;
    Eigen::MatrixXf m_features;
    Eigen::VectorXi m_labels;

};

#endif // NEURALNETWORKTRAINER_H
