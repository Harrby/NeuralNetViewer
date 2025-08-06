
#ifndef NERUALNETWORK_H
#define NERUALNETWORK_H

#include "neuralnetoptionsdata.h"
#include "layer.h"
#include "loss.h"
#include "optimiser.h"
#include <QObject>
#include "epochstats.h"
#include "metrics.h"
#include <atomic>

class NeuralNetwork : public QObject
{
    Q_OBJECT

public:
    NeuralNetwork(NeuralNetOptionsData& network_parameters, QObject* parent = nullptr);
    void initialise_network();
    void train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels);
    int predict(const Eigen::VectorXf& inputs);
    Metrics validate(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels) const;

    void requestCancel();
    bool isCancelled() const;
    void resetCancel();

private:
    NeuralNetOptionsData& m_network_parameters;
    std::vector<std::unique_ptr<Layer>> m_layers;
    std::vector<std::unique_ptr<ActivationFunction>> m_activation_functions;
    const LossFunction& m_loss_function;
    const Optimiser& m_optimiser;
    std::atomic<bool> m_cancel_requested { false };

signals:
    void epochDataChanged(EpochStats);


};

#endif // NERUALNETWORK_H
