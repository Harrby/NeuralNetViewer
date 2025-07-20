
#ifndef LOSS_H
#define LOSS_H

#include <Eigen/Dense>
#include "neuralnetoptionsdata.h"


class LossFunction {
public:
    virtual float forward(const Eigen::VectorXf& logits, int true_class) const = 0;
    virtual Eigen::VectorXf backward(const Eigen::VectorXf& logits, int true_class) const = 0;
    virtual ~LossFunction() = default;
};

class CategoricalCrossEntropyLoss : public LossFunction {
public:
    float forward(const Eigen::VectorXf& logits, int true_class) const override;
    Eigen::VectorXf backward(const Eigen::VectorXf& logits, int true_class) const override;
};



const LossFunction& get_loss_function(LossFunctionType type);


#endif // LOSS_H
