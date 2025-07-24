
#ifndef NERUALNETWORK_H
#define NERUALNETWORK_H

#include "neuralnetoptionsdata.h"
#include "layer.h"
#include "loss.h"
#include "optimiser.h"

class NeuralNetwork
{
public:
    NeuralNetwork(NeuralNetOptionsData& network_parameters);
    void initialise_layers();
    void train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels);
    int predict(const Eigen::VectorXf& inputs);
private:
    NeuralNetOptionsData& m_network_parameters;
    std::vector<std::unique_ptr<Layer>> m_layers;
    const LossFunction& m_loss_function;
    const Optimiser& m_optimiser;


};

#endif // NERUALNETWORK_H
