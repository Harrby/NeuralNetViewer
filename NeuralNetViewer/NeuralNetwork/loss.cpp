
#include "loss.h"


float CategoricalCrossEntropyLoss::forward(const Eigen::VectorXf& logits, int true_class) const{
    Eigen::VectorXf shifted = logits.array() - logits.maxCoeff();
    float log_sum_exp = std::log(shifted.array().exp().sum());
    return -shifted(true_class) + log_sum_exp;
}

Eigen::VectorXf CategoricalCrossEntropyLoss::backward(const Eigen::VectorXf& logits, int true_class) const{
    Eigen::VectorXf shifted = logits.array() - logits.maxCoeff();
    Eigen::VectorXf softmax = shifted.array().exp();
    softmax /= softmax.sum();
    softmax(true_class) -= 1.0f;  // ∇(softmax + CCE)
    return softmax;
}


const LossFunction& get_loss_function(LossFunctionType type)
{
    switch (type) {
    case LossFunctionType::CategoricalCrossEntropy:        {static CategoricalCrossEntropyLoss cce;        return cce;}
    default: throw std::runtime_error("Unsupported activation");
    }
}
