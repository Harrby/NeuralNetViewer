
#include "activation.h"



Eigen::VectorXf ReLU::forward(const Eigen::VectorXf& input) const{
    return input.unaryExpr([](float x) { return std::max(0.0f, x); });
}

Eigen::VectorXf ReLU::backward(const Eigen::VectorXf& dvalues, const Eigen::VectorXf& inputs) const{
    return dvalues.cwiseProduct(inputs.unaryExpr([](float v){ return v > 0.0f ? 1.0f : 0.0f; }));
}



Eigen::VectorXf Identity::forward(const Eigen::VectorXf& input) const {
    return input.unaryExpr([](float x) { return x; });
}

Eigen::VectorXf Identity::backward(const Eigen::VectorXf& dvalues, const Eigen::VectorXf& inputs) const {
    return dvalues;
}

const ActivationFunction& get_activation(ActivationFunctionType type)
{
    switch (type) {
    case ActivationFunctionType::ReLU:        {static ReLU relu;        return relu;}
    case ActivationFunctionType::LeakyReLU:   {static Identity leaky;  return leaky;}
    case ActivationFunctionType::Identity:    {static Identity id;      return id;}
    case ActivationFunctionType::Sigmoid:     {static Identity sig;      return sig;}
    case ActivationFunctionType::Tanh:        {static Identity tanh;        return tanh;}
    case ActivationFunctionType::Softmax:     {static Identity sm;       return sm;}
    default: throw std::runtime_error("Unsupported activation");
    }
}

