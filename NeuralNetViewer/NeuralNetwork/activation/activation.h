
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <Eigen/Dense>
#include "activation_utils.h"


class ActivationFunction {
public:

    virtual Eigen::MatrixXf forward (const Eigen::MatrixXf& x) = 0;
    virtual Eigen::MatrixXf backward(const Eigen::MatrixXf& dOut) = 0;
    virtual ~ActivationFunction() = default;

protected:
    Eigen::MatrixXf m_outputs;
    Eigen::MatrixXf m_inputs;
};

class ReLU : public ActivationFunction {
public:
    Eigen::MatrixXf forward(const Eigen::MatrixXf& input)  override;
    Eigen::MatrixXf backward(const Eigen::MatrixXf& dvalues)  override;
};

class LeakyReLU : public ActivationFunction {
private:
    float alpha = 0.01f;

public:
    Eigen::MatrixXf forward(const Eigen::MatrixXf& input)  override;
    Eigen::MatrixXf backward(const Eigen::MatrixXf& dvalues)  override;
};

class Sigmoid : public ActivationFunction {

public:
    Eigen::MatrixXf forward(const Eigen::MatrixXf& input)  override;
    Eigen::MatrixXf backward(const Eigen::MatrixXf& dvalues)  override;
};

class Tanh : public ActivationFunction {
public:
    Eigen::MatrixXf forward(const Eigen::MatrixXf& input)  override;
    Eigen::MatrixXf backward(const Eigen::MatrixXf& dvalues)  override;
};


class Identity : public ActivationFunction {
public:
    Eigen::MatrixXf forward(const Eigen::MatrixXf& input)  override;
    Eigen::MatrixXf backward(const Eigen::MatrixXf& dvalues)  override;
};

class Softmax : public ActivationFunction {
public:
    Eigen::MatrixXf forward(const Eigen::MatrixXf& input)  override;
    Eigen::MatrixXf backward(const Eigen::MatrixXf& dvalues)  override;
};





// OTHERS NOT IMPLEMENTED YET
std::unique_ptr<ActivationFunction> get_activation(ActivationFunctionType type);


#endif // ACTIVATION_H
