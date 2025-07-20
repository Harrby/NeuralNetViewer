
#ifndef NERUALNETWORK_H
#define NERUALNETWORK_H

#include "neuralnetoptionsdata.h"
#include "layer.h"
#include "loss.h"

class NeuralNetwork
{
public:
    NeuralNetwork(NeuralNetOptionsData& network_parameters);
    void initialise_layers();
    void train(const Eigen::MatrixXf& inputs, const Eigen::VectorXi& labels);
private:
    NeuralNetOptionsData& m_network_parameters;
    std::vector<std::unique_ptr<Layer>> m_layers;
    const LossFunction& m_loss_function;


};

#endif // NERUALNETWORK_H
