
#ifndef OPTIMISER_H
#define OPTIMISER_H
#include <Eigen/Dense>
#include "optimiser_utils.h"
#include "optimiser_params.h"
#include <QDebug>
#include <cmath>

class Optimiser
{
public:
    Optimiser() = default;
    virtual void update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad) = 0;
    virtual void update(Eigen::VectorXf& param, const Eigen::VectorXf& grad) = 0;
    virtual void setParams(OptimiserParams optimiser_params) = 0;
};

class SGD : public Optimiser {
public:
    SGD(float learning_rate);
    void update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad)  override;
    void update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  override;
    void setParams(OptimiserParams optimiser_params) override;

private:
    float learning_rate;
};

class MomentumSGD : public Optimiser {
public:
    MomentumSGD(float learning_rate, float momentum);

    void update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad)  override;
    void update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  override;
    void setParams(OptimiserParams optimiser_params) override;

private:
    float learning_rate;
    float momentum;
    std::unordered_map<const void*, Eigen::MatrixXf> velocity_matrices;
    std::unordered_map<const void*, Eigen::VectorXf> velocity_vectors;

};


class RMSProp : public Optimiser {
public:
    RMSProp(float learning_rate, float beta2, float epsilon);
    void update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad)  override;
    void update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  override;
    void setParams(OptimiserParams optimiser_params) override;

private:
    float learning_rate;
    float beta2;
    float epsilon;
    std::unordered_map<const void*, Eigen::MatrixXf> squared_grad_avg_weights;
    std::unordered_map<const void*, Eigen::VectorXf> squared_grad_avg_biases;

};


class Adam : public Optimiser {
public:
    Adam(float learning_rate, float beta1, float beta2, float epsilon);
    void update(Eigen::MatrixXf& param, const Eigen::MatrixXf& grad)  override;
    void update(Eigen::VectorXf& param, const Eigen::VectorXf& grad)  override;
    void setParams(OptimiserParams optimiser_params) override;

private:
    float learning_rate;
    float beta1;
    float beta2;
    float beta1_pow_t;
    float beta2_pow_t;
    float epsilon;
    int t;
    std::unordered_map<const void*, Eigen::MatrixXf> first_moment_estimate_matrix;
    std::unordered_map<const void*, Eigen::VectorXf> first_moment_estimate_vector;
    std::unordered_map<const void*, Eigen::MatrixXf> second_moment_estimate_matrix;
    std::unordered_map<const void*, Eigen::VectorXf> second_moment_estimate_vector;
};

std::unique_ptr<Optimiser> get_optimiser_function(OptimiserType type, float learning_rate, float momentum, float beta1, float beta2, float epsilon);



#endif // OPTIMISER_H
