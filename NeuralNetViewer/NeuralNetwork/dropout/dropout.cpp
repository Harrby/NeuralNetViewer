
#include "dropout.h"

Dropout::Dropout(double dropout_rate)
    : m_dropout_rate(dropout_rate),
    m_keep_prob(1.0 - dropout_rate),
    m_generator(std::random_device{}()),
    m_uniform_dist(0.0, 1.0)
{

}

Eigen::MatrixXf Dropout::apply(const Eigen::MatrixXf& activations, bool training){
    if (!training || m_dropout_rate <=0){
        return activations;
    }

    Eigen::MatrixXf rand_mat(activations.rows(), activations.cols());
    for (int i = 0; i < rand_mat.size(); i++) {
        rand_mat.data()[i] = m_uniform_dist(m_generator);
    }

    m_mask = (rand_mat.array() < m_keep_prob).cast<float>();
    return (activations.array() * m_mask.array()) / m_keep_prob;

}
