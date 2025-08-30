
#include "loss.h"

Eigen::VectorXf CategoricalCrossEntropyLoss::forward(const Eigen::MatrixXf& logits, const Eigen::VectorXi& true_classes) const{
    Eigen::VectorXf rowMax = logits.rowwise().maxCoeff();
    Eigen::MatrixXf shifted = logits.colwise() - rowMax;

    Eigen::VectorXf log_sum_exp = shifted.array().exp().rowwise().sum().log();

    Eigen::VectorXf picked(shifted.rows());
    for (int i = 0; i < shifted.rows(); ++i) {
        picked(i) = shifted(i, (int)true_classes(i));
    }

    Eigen::VectorXf losses = -picked + log_sum_exp;
    return losses;
}

Eigen::MatrixXf CategoricalCrossEntropyLoss::backward(const Eigen::MatrixXf& logits, const Eigen::VectorXi& true_classes) const {
    Eigen::VectorXf rowMax = logits.rowwise().maxCoeff();
    //qDebug() << logits.rows();
    //qDebug() << logits.cols();
    //qDebug() << rowMax.rows();
    //qDebug() << rowMax.cols();

    Eigen::MatrixXf shifted = logits.colwise() - rowMax;

    Eigen::MatrixXf softmax = shifted.array().exp();
    softmax = softmax.array().colwise() / softmax.rowwise().sum().array();

    for (int i = 0; i < shifted.rows(); ++i) {
        softmax(i, true_classes(i)) -= 1.0f;
    }
    return softmax;
}


const LossFunction& get_loss_function(LossFunctionType type)
{
    switch (type) {
    case LossFunctionType::CategoricalCrossEntropy:        {static CategoricalCrossEntropyLoss cce;        return cce;}
    default: throw std::runtime_error("Unsupported activation");
    }
}
