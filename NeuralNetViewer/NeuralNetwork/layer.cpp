
#include "layer.h"

Layer::Layer(int input_size, const NeuralNetLayerData& parameters)
    : m_input_size(input_size),
    m_parameters(parameters),
    m_weights(initialise_weights()),
    m_biases(initialise_biases()),
    m_activation(get_activation(parameters.activation_function))

{

}

Eigen::MatrixXf Layer::initialise_weights(){

    // He init
    Eigen::MatrixXf weights(m_parameters.neurons, m_input_size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0.0f, std::sqrt(2.0f / m_input_size));  // m = fan_in

    for (int i=0; i < weights.rows(); ++i){
        for (int j=0; j < weights.cols(); ++j){
            weights(i, j) = dist(gen);
        }
    }

    return weights;

}

Eigen::VectorXf Layer::initialise_biases(){
    return Eigen::VectorXf::Zero(m_parameters.neurons);
    }



Eigen::VectorXf Layer::forward(const Eigen::VectorXf& inputs){
    m_inputs = inputs;
    Eigen::VectorXf output = m_weights * inputs + m_biases;
    return m_activation.forward(output);
}

Eigen::VectorXf Layer::backward(const Eigen::VectorXf& grad_from_next_layer, bool accumulate){
    Eigen::VectorXf adjusted_dvalues = m_activation.backward(grad_from_next_layer, m_inputs);
    if (accumulate){
        m_dweights += m_inputs * adjusted_dvalues.transpose();
        m_dbiases += adjusted_dvalues;
    } else{
    m_dweights = m_inputs * adjusted_dvalues.transpose();
    m_dbiases = adjusted_dvalues;
    }

    Eigen::VectorXf dinputs = m_weights * adjusted_dvalues;
    return dinputs;
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



