
#include "activation.h"



Eigen::MatrixXf ReLU::forward(const Eigen::MatrixXf& x){

    m_output = x.cwiseMax(0.0f);
    return m_output;;
}

Eigen::MatrixXf ReLU::backward(const Eigen::MatrixXf& dvalues) {
    Eigen::MatrixXf grad = (m_output.array() > 0).cast<float>();
    return grad.array() * dvalues.array();
}



Eigen::MatrixXf Identity::forward(const Eigen::MatrixXf& input)  {
    m_output = input.unaryExpr([](float x) { return x; });
    return m_output;
}

Eigen::MatrixXf Identity::backward(const Eigen::MatrixXf& dvalues)  {
    return dvalues;
}

std::unique_ptr<ActivationFunction> get_activation(ActivationFunctionType type)
{
    switch (type) {
    case ActivationFunctionType::ReLU:        return std::make_unique<ReLU>();
    case ActivationFunctionType::LeakyReLU:   return std::make_unique<Identity>();
    case ActivationFunctionType::Identity:    return std::make_unique<Identity>();
    case ActivationFunctionType::Sigmoid:     return std::make_unique<Identity>();
    case ActivationFunctionType::Tanh:        return std::make_unique<Identity>();
    case ActivationFunctionType::Softmax:     return std::make_unique<Identity>();
    default: throw std::runtime_error("Unsupported activation");
    }
}

