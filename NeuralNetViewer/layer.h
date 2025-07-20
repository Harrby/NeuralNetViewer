
#ifndef LAYER_H
#define LAYER_H

#include "neuralnetlayerdata.h"
#include <Eigen/Dense>
#include <random>
#include <../activation.h>

class Layer
{
public:
    Layer(int input_size, const NeuralNetLayerData& parameters);

    Eigen::VectorXf forward(const Eigen::VectorXf& inputs);
    Eigen::VectorXf backward(const Eigen::VectorXf& grad_from_next_layer);

private:
    int m_input_size;
    const NeuralNetLayerData& m_parameters;

    Eigen::MatrixXf initialise_weights();
    Eigen::VectorXf initialise_biases();

    Eigen::VectorXf m_inputs;
    Eigen::MatrixXf m_weights;
    Eigen::VectorXf m_biases;
    Eigen::MatrixXf m_dweights;
    Eigen::VectorXf m_dbiases;
    const ActivationFunction& m_activation;


};

#endif // LAYER_H
