
#ifndef NERUALNETWORK_H
#define NERUALNETWORK_H

#include "neuralnetoptionsdata.h"
#include "layer.h"
#include "loss.h"
#include "optimiser.h"
#include <QObject>
#include "epochstats.h"
#include "metrics.h"

class NeuralNetwork : public QObject
{
    Q_OBJECT

public:
    NeuralNetwork(NeuralNetOptionsData& network_parameters, QObject* parent = nullptr);
    void initialise_layers();
    void train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels);
    int predict(const Eigen::VectorXf& inputs);
    Metrics validate(const Eigen::MatrixXf& inputs, Eigen::VectorXi& labels) const;
private:
    NeuralNetOptionsData& m_network_parameters;
    std::vector<std::unique_ptr<Layer>> m_layers;
    const LossFunction& m_loss_function;
    const Optimiser& m_optimiser;

signals:
    void epochDataChanged(EpochStats);


};

#endif // NERUALNETWORK_H
