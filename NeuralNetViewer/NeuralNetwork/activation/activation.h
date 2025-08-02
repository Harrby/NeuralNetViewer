
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <Eigen/Dense>
#include "activation_utils.h"


class ActivationFunction {
public:
    virtual Eigen::VectorXf forward (const Eigen::VectorXf& x) const = 0;
    virtual Eigen::VectorXf backward(const Eigen::VectorXf& dOut,
                                     const Eigen::VectorXf& cached) const = 0;
    virtual ~ActivationFunction() = default;
};

class ReLU : public ActivationFunction {
public:
    Eigen::VectorXf forward(const Eigen::VectorXf& input) const override;
    Eigen::VectorXf backward(const Eigen::VectorXf& dvalues, const Eigen::VectorXf& inputs) const override;
};


class Identity : public ActivationFunction {
public:
    Eigen::VectorXf forward(const Eigen::VectorXf& input) const override;
    Eigen::VectorXf backward(const Eigen::VectorXf& dvalues, const Eigen::VectorXf& inputs) const override;
};


// OTHERS NOT IMPLEMENTED YET
const ActivationFunction& get_activation(ActivationFunctionType type);


#endif // ACTIVATION_H
