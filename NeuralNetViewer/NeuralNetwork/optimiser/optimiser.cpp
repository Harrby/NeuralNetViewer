
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

    velocity = momentum * velocity + (1-momentum) * grad;
    param -= learning_rate * velocity;

    qDebug() << "new param" << param.norm();
}

void MomentumSGD::update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  {
    auto key = static_cast<const void*>(param.data());
    Eigen::VectorXf& velocity = velocity_vectors[key];

    if (velocity.size() == 0){
        velocity = Eigen::VectorXf::Zero(param.size());
    }

    velocity = momentum * velocity + (1-momentum) * grad;
    param -= learning_rate * velocity;

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
    param -= ((learning_rate * grad.array()) / (Eg2.array().sqrt() + epsilon)).matrix();
}

void RMSProp::update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  {
    auto key = static_cast<const void*>(param.data());
    Eigen::VectorXf& Eg2 = squared_grad_avg_biases[key];

    if (Eg2.size() == 0){
        Eg2 = Eigen::VectorXf::Zero(param.size());
    }

    Eg2 = beta2 * Eg2 + (1.0f - beta2) * grad.array().square().matrix();
    param -= ((learning_rate * grad.array()) / (Eg2.array().sqrt() + epsilon)).matrix();
}

void RMSProp::setParams(OptimiserParams optimiser_params)  {
    learning_rate = optimiser_params.learning_rate;
    beta2 = optimiser_params.beta2;
    epsilon = optimiser_params.epsilon;
}


Adam::Adam(float learing_rate, float beta1, float beta2, float epsilon)
    : learning_rate(learing_rate),
    beta1(beta1),
    beta2(beta2),
    beta1_pow_t(1.0f),
    beta2_pow_t(1.0f),
    epsilon(epsilon),
    t(1)

{}

void Adam::update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad){
    auto key = static_cast<const void*>(param.data());
    Eigen::MatrixXf& M1 = first_moment_estimate_matrix[key];
    Eigen::MatrixXf& M2 = second_moment_estimate_matrix[key];

    if (M1.size() == 0){
        M1 = Eigen::MatrixXf::Zero(param.rows(), param.cols());
    }
    if (M2.size() == 0){
        M2 = Eigen::MatrixXf::Zero(param.rows(), param.cols());
    }

    M1 = beta1 * M1 + (1 - beta1) * grad;
    M2 = beta2 * M2 + (1 - beta2) * grad.array().square().matrix();

    beta1_pow_t *= beta1;
    beta2_pow_t *= beta2;

    Eigen::MatrixXf M1_corrected = M1 / (1 - beta1_pow_t);
    Eigen::MatrixXf M2_corrected = M2 / (1 - beta2_pow_t);


    param -= (learning_rate * (M1_corrected.array()) / (M2_corrected.array().sqrt() + epsilon)).matrix();
}

void Adam::update(Eigen::VectorXf& param, const Eigen::VectorXf& grad){
    auto key = static_cast<const void*>(param.data());
    Eigen::VectorXf& M1 = first_moment_estimate_vector[key];
    Eigen::VectorXf& M2 = second_moment_estimate_vector[key];

    if (M1.size() == 0){
        M1 = Eigen::VectorXf::Zero(param.size());
    }
    if (M2.size() == 0){
        M2 = Eigen::VectorXf::Zero(param.size());
    }

    M1 = beta1 * M1 + (1 - beta1) * grad;
    M2 = beta2 * M2 + (1 - beta2) * grad.array().square().matrix();

    beta1_pow_t *= beta1;
    beta2_pow_t *= beta2;

    Eigen::VectorXf M1_corrected = M1 / (1 - beta1_pow_t);
    Eigen::VectorXf M2_corrected = M2 / (1 - beta2_pow_t);

    param -= (learning_rate * (M1_corrected.array()) / (M2_corrected.array().sqrt() + epsilon)).matrix();
}

void Adam::setParams(OptimiserParams params){
    learning_rate = params.learning_rate;
    beta1 = params.beta1;
    beta2 = params.beta2;
    epsilon = params.epsilon;
}

std::unique_ptr<Optimiser> get_optimiser_function(OptimiserType type,  float learning_rate,  float momentum,  float beta1, float beta2, float epsilon)
{
    switch (type) {
    case OptimiserType::SGD:         return std::make_unique<SGD>(learning_rate);
    case OptimiserType::MomentumSGD: return std::make_unique<MomentumSGD>(learning_rate, momentum);
    case OptimiserType::RMSProp:     return std::make_unique<RMSProp>(learning_rate, beta2, epsilon);
    case OptimiserType::Adam:        return std::make_unique<Adam>(learning_rate, beta1, beta2, epsilon);

    default: throw std::runtime_error("Unsupported optimiser");
    }
}
