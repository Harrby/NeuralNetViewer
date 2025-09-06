
#ifndef DROPOUT_H
#define DROPOUT_H

#include <Eigen/Dense>
#include <random>

class Dropout
{
public:
    Dropout(double dropout_rate);

    Eigen::MatrixXf apply(const Eigen::MatrixXf& activations, bool training);

private:
    double m_dropout_rate;
    double m_keep_prob;
    std::mt19937 m_generator;
    std::uniform_real_distribution<float> m_uniform_dist;
    Eigen::MatrixXf m_mask;
};

#endif // DROPOUT_H
