
#ifndef OPTIMISER_H
#define OPTIMISER_H
#include <Eigen/Dense>
#include "neuralnetoptionsdata.h"


class Optimiser
{
public:
    Optimiser() = default;
    virtual void update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad, float learning_rate) const = 0;
    virtual void update(Eigen::VectorXf& param, const Eigen::VectorXf& grad, float learning_rate) const = 0;

};

class SGD : public Optimiser {
    void update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad, float learning_rate) const override;
    void update(Eigen::VectorXf& param, const Eigen::VectorXf& grad, float learning_rate) const override;
};


const Optimiser& get_optimiser_function(OptimiserType type);



#endif // OPTIMISER_H
