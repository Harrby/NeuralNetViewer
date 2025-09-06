
#include "layer.h"

Layer::Layer(int input_size, const NeuralNetLayerData& parameters)
    : m_input_size(input_size),
    m_parameters(parameters),
    m_weights(initialise_weights()),
    m_biases(initialise_biases()),
    m_dweights(initialise_grad_weights()),
    m_dbiases(initialise_grad_biases())

{

}

Eigen::MatrixXf Layer::initialise_weights(){
   return get_weight_init(m_parameters.weight_initialisation,
                           m_input_size,
                           m_parameters.neurons);
}

Eigen::VectorXf Layer::initialise_biases(){
    return Eigen::VectorXf::Zero(m_parameters.neurons);
    }

Eigen::MatrixXf Layer::initialise_grad_weights(){
    return Eigen::MatrixXf::Zero(m_parameters.neurons, m_input_size);
}

Eigen::VectorXf Layer::initialise_grad_biases(){
    return Eigen::VectorXf::Zero(m_parameters.neurons);
}



Eigen::MatrixXf Layer::forward(const Eigen::MatrixXf& batch_inputs){
    m_inputs = batch_inputs;
    Eigen::MatrixXf broadcasted_biases = m_biases.transpose().replicate(batch_inputs.rows(), 1);
    m_outputs = batch_inputs * m_weights.transpose();

    m_outputs += broadcasted_biases;
    return m_outputs;
}

Eigen::MatrixXf Layer::backward(const Eigen::MatrixXf& grad_output, bool accumulate){
    Eigen::MatrixXf grad_W = grad_output.transpose() * m_inputs;
    Eigen::VectorXf grad_b = grad_output.colwise().sum().transpose();
    if (accumulate){
        m_dweights += grad_W;
        m_dbiases += grad_b;
    } else{
    m_dweights = grad_W;
    m_dbiases = grad_b;
    }
    Eigen::MatrixXf grad_input = grad_output * m_weights;
    return grad_input;
}

void Layer::scaleGradients(float factor){
    m_dweights *= factor;
    m_dbiases *= factor;
};

void Layer::zeroGradients(){
    m_dweights.setZero();
    m_dbiases.setZero();
}

Eigen::MatrixXf& Layer::getWeights(){
    return m_weights;
};

const Eigen::MatrixXf& Layer::getWeights() const{
    return m_weights;
};


Eigen::VectorXf& Layer::getBiases(){
    return m_biases;
}

const Eigen::VectorXf& Layer::getBiases() const{
    return m_biases;
}

Eigen::MatrixXf& Layer::getWeightGradients(){
    return m_dweights;
};
const Eigen::VectorXf& Layer::getBiasGradients() const{
    return m_dbiases;
};



