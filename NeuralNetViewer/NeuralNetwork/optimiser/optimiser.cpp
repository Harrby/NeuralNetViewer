
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

RMSProp::RMSProp(float learning_rate, float beta2, float epsilon)
    : learning_rate(learning_rate),
      beta2(beta2),
      epsilon(epsilon)
{}

void RMSProp::update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad){
    auto key = static_cast<const void*>(param.data());
    Eigen::MatrixXf& Eg2 = squared_grad_avg_weights[key];

    if (Eg2.size() == 0){
        Eg2 = Eigen::MatrixXf::Zero(param.rows(), param.cols());
    }

    Eg2 = beta2 * Eg2 + (1.0f - beta2) * grad.array().square().matrix();
    param -= (learning_rate * grad.array() / (Eg2.array().sqrt() + epsilon)).matrix();
}

void RMSProp::update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  {
    auto key = static_cast<const void*>(param.data());
    Eigen::VectorXf& Eg2 = squared_grad_avg_biases[key];

    if (Eg2.size() == 0){
        Eg2 = Eigen::VectorXf::Zero(param.size());
    }

    Eg2 = beta2 * Eg2 + (1.0f - beta2) * grad.array().square().matrix();
    param -= (learning_rate * grad.array() / (Eg2.array().sqrt() + epsilon)).matrix();
}

void RMSProp::setParams(OptimiserParams optimiser_params)  {
    learning_rate = optimiser_params.learning_rate;
    beta2 = optimiser_params.beta2;
    epsilon = optimiser_params.epsilon;
}




std::unique_ptr<Optimiser> get_optimiser_function(OptimiserType type,  float learning_rate,  float momentum,  float beta1, float beta2, float epsilon)
{
    switch (type) {
    case OptimiserType::SGD:         return std::make_unique<SGD>(learning_rate);
    case OptimiserType::MomentumSGD: return std::make_unique<MomentumSGD>(learning_rate, momentum);
    case OptimiserType::RMSProp:     return std::make_unique<RMSProp>(learning_rate, beta2, epsilon);

    default: throw std::runtime_error("Unsupported optimiser");
    }
}
