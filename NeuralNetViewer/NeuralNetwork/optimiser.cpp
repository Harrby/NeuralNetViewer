
#include "optimiser.h"


void SGD::update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad, float learning_rate) const {
    param -= learning_rate * grad;
}

void SGD::update(Eigen::VectorXf& param, const Eigen::VectorXf& grad, float learning_rate) const {
    param -= learning_rate * grad;
}

const Optimiser& get_optimiser_function(OptimiserType type)
{
    switch (type) {
    case OptimiserType::SGD:        {static SGD sgd;        return sgd;}
    default: throw std::runtime_error("Unsupported optimiser");
    }
}
