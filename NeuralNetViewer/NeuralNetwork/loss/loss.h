
#ifndef LOSS_H
#define LOSS_H

#include <Eigen/Dense>
#include "loss_utils.h"


class LossFunction {
public:
    virtual float forward(const Eigen::MatrixXf& logits, Eigen::VectorXi& true_classes) const = 0;
    virtual Eigen::MatrixXf backward(const Eigen::MatrixXf& logits, Eigen::VectorXi& true_classes) const = 0;
    virtual ~LossFunction() = default;
};

class CategoricalCrossEntropyLoss : public LossFunction {
public:
    float forward(const Eigen::MatrixXf& logits, Eigen::VectorXi& true_classes) const override;
    Eigen::MatrixXf backward(const Eigen::MatrixXf& logits, Eigen::VectorXi& true_classes) const override;
};



const LossFunction& get_loss_function(LossFunctionType type);


#endif // LOSS_H
