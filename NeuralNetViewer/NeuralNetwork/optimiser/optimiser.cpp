
#include "optimiser.h"

SGD::SGD(float learning_rate)
    :learning_rate(learning_rate)
{

}


void SGD::update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad)  {
    param -= learning_rate * grad;
}

void SGD::update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  {
    param -= learning_rate * grad;
}

void SGD::setParams(OptimiserParams optimiser_params){
    learning_rate = optimiser_params.learning_rate;
}

MomentumSGD::MomentumSGD(float learning_rate, float momentum_ref)
    : learning_rate(learning_rate),
    momentum(momentum_ref)
{

}

void MomentumSGD::update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad) {
    auto key = static_cast<const void*>(param.data());
    Eigen::MatrixXf& velocity = velocity_matrices[key];

    if (velocity.size() == 0){
        velocity = Eigen::MatrixXf::Zero(param.rows(), param.cols());
    }

    velocity = momentum * velocity - learning_rate * grad;
    param += velocity;

    qDebug() << "new param" << param.norm();
}

void MomentumSGD::update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  {
    auto key = static_cast<const void*>(param.data());
    Eigen::VectorXf& velocity = velocity_vectors[key];

    if (velocity.size() == 0){
        velocity = Eigen::VectorXf::Zero(param.size());
    }

    velocity = momentum * velocity - learning_rate * grad;
    param += velocity;

    qDebug() << "new param" << param.size();
}

void MomentumSGD::setParams(OptimiserParams optimiser_params){
    learning_rate = optimiser_params.learning_rate;
    momentum = optimiser_params.momentum;
}



std::unique_ptr<Optimiser> get_optimiser_function(OptimiserType type,  float learning_rate,  float momentum,  float beta1, float beta2, float epsilon)
{
    switch (type) {
    case OptimiserType::SGD:         return std::make_unique<SGD>(learning_rate);
    case OptimiserType::MomentumSGD: return std::make_unique<MomentumSGD>(learning_rate, momentum);
    default: throw std::runtime_error("Unsupported optimiser");
    }
}
