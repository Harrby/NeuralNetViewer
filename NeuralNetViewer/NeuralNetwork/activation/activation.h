
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <Eigen/Dense>
#include "activation_utils.h"


class ActivationFunction {
public:
    virtual Eigen::VectorXf forward (const Eigen::VectorXf& x) = 0;
    virtual Eigen::VectorXf backward(const Eigen::VectorXf& dOut) = 0;
    virtual ~ActivationFunction() = default;

protected:
    Eigen::VectorXf m_output;
};

class ReLU : public ActivationFunction {
public:
    Eigen::VectorXf forward(const Eigen::VectorXf& input)  override;
    Eigen::VectorXf backward(const Eigen::VectorXf& dvalues)  override;
};


class Identity : public ActivationFunction {
public:
    Eigen::VectorXf forward(const Eigen::VectorXf& input)  override;
    Eigen::VectorXf backward(const Eigen::VectorXf& dvalues)  override;
};


// OTHERS NOT IMPLEMENTED YET
std::unique_ptr<ActivationFunction> get_activation(ActivationFunctionType type);


#endif // ACTIVATION_H
