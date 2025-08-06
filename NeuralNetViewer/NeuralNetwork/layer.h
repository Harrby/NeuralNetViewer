
#ifndef LAYER_H
#define LAYER_H

#include "neuralnetlayerdata.h"
#include <Eigen/Dense>
#include <random>
#include <activation.h>
#include "initialisation.h"
#include <QDebug>

class Layer
{
public:
    Layer(int input_size, const NeuralNetLayerData& parameters);

    Eigen::VectorXf forward(const Eigen::VectorXf& inputs);
    Eigen::VectorXf backward(const Eigen::VectorXf& grad_from_next_layer, bool accumulate);

    Eigen::MatrixXf& getWeights();
    const Eigen::MatrixXf& getWeights() const;
    Eigen::VectorXf& getBiases();
    const Eigen::VectorXf& getBiases() const;
    Eigen::MatrixXf& getWeightGradients();
    const Eigen::VectorXf& getBiasGradients() const;

    void zeroGradients();
    void scaleGradients(float factor);

private:
    int m_input_size;
    const NeuralNetLayerData& m_parameters;

    Eigen::MatrixXf initialise_weights();
    Eigen::VectorXf initialise_biases();
    Eigen::MatrixXf initialise_weight_gradients();
    Eigen::VectorXf initialise_bias_gradients();
    Eigen::MatrixXf initialise_grad_weights();
    Eigen::VectorXf initialise_grad_biases();


    Eigen::VectorXf m_input;
    Eigen::VectorXf m_output;
    Eigen::MatrixXf m_weights;
    Eigen::VectorXf m_biases;
    Eigen::MatrixXf m_dweights;
    Eigen::VectorXf m_dbiases;




};

#endif // LAYER_H
