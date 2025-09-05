
#include "activation.h"



Eigen::MatrixXf ReLU::forward(const Eigen::MatrixXf& x){
    m_inputs = x;
    m_outputs = x.cwiseMax(0.0f);
    return m_outputs;
}

Eigen::MatrixXf ReLU::backward(const Eigen::MatrixXf& dvalues) {
    Eigen::MatrixXf dinputs = dvalues.array() * (m_inputs.array() > 0.0f).cast<float>();
    return dinputs;
}


Eigen::MatrixXf LeakyReLU::forward(const Eigen::MatrixXf& x){
    m_inputs = x;
    Eigen::MatrixXf pos = x.cwiseMax(0.0f);
    Eigen::MatrixXf neg = x.cwiseMin(0.0f);



    m_outputs = pos + alpha * neg;
    return m_outputs;
}

Eigen::MatrixXf LeakyReLU::backward(const Eigen::MatrixXf& dvalues){
    Eigen::ArrayXXf mask = ((m_inputs.array() > 0.0f).cast<float>() + (m_inputs.array() < 0.0f).cast<float>() * alpha);
    Eigen::MatrixXf dinputs = dvalues.array() * mask;
    return dinputs;
}


Eigen::MatrixXf Sigmoid::forward(const Eigen::MatrixXf& x){
    m_inputs = x;
    m_outputs = 1.0f / (1.0f + (-x.array()).exp());
    return m_outputs;

};

Eigen::MatrixXf Sigmoid::backward(const Eigen::MatrixXf& dvalues) {
    Eigen::MatrixXf dsigma = m_outputs.array() * (1.0f - m_outputs.array());
    Eigen::MatrixXf dinputs = dvalues.array() * dsigma.array();
    return dinputs;
}

Eigen::MatrixXf Tanh::forward(const Eigen::MatrixXf& x) {
    m_inputs = x;
    m_outputs = x.array().tanh();
    return m_outputs;
}

Eigen::MatrixXf Tanh::backward(const Eigen::MatrixXf& dvalues) {
    Eigen::MatrixXf dtanh = 1.0f - m_outputs.array().square();
    Eigen::MatrixXf dinputs = dvalues.array() * dtanh.array();
    return dinputs;
}



Eigen::MatrixXf Identity::forward(const Eigen::MatrixXf& input)  {
    m_inputs = input;
    m_outputs = input.unaryExpr([](float x) { return x; });
    //qDebug() << "saved m outputs in identity as" << m_outputs.rows() << m_outputs.cols();

    return m_outputs;
}

Eigen::MatrixXf Identity::backward(const Eigen::MatrixXf& dvalues)  {
    //qDebug() << "called id backward";
    return dvalues;
}


Eigen::MatrixXf Softmax::forward(const Eigen::MatrixXf& x) {
    // Save inputs for backward
    m_inputs = x;

    // For numerical stability: subtract rowwise max
    Eigen::VectorXf rowMax = x.rowwise().maxCoeff();
    Eigen::MatrixXf shifted = x.colwise() - rowMax;

    // Exponentiate
    Eigen::MatrixXf exp_shifted = shifted.array().exp();

    // Normalize rowwise
    Eigen::VectorXf rowSums = exp_shifted.rowwise().sum();
    m_outputs = exp_shifted.array().colwise() / rowSums.array();

    return m_outputs;
}

Eigen::MatrixXf Softmax::backward(const Eigen::MatrixXf& dvalues) {
    const int B = m_outputs.rows();
    const int C = m_outputs.cols();
    Eigen::MatrixXf dinputs(B, C);

    for (int i = 0; i < B; ++i) {
        // y: Cx1 column vector of probs
        Eigen::VectorXf y = m_outputs.row(i).transpose();
        // J = diag(y) - y y^T   (CxC)
        Eigen::MatrixXf J = y.asDiagonal().toDenseMatrix() - (y * y.transpose());
        // upstream grad is 1xC row; keep it as row * J -> 1xC row
        dinputs.row(i) = dvalues.row(i) * J;
    }
    return dinputs;
}

std::unique_ptr<ActivationFunction> get_activation(ActivationFunctionType type)
{
    switch (type) {
    case ActivationFunctionType::ReLU:        return std::make_unique<ReLU>();
    case ActivationFunctionType::LeakyReLU:   return std::make_unique<LeakyReLU>();
    case ActivationFunctionType::Identity:    return std::make_unique<Identity>();
    case ActivationFunctionType::Sigmoid:     return std::make_unique<Sigmoid>();
    case ActivationFunctionType::Tanh:        return std::make_unique<Tanh>();
    case ActivationFunctionType::Softmax:     return std::make_unique<Softmax>();
    default: throw std::runtime_error("Unsupported activation");
    }
}

