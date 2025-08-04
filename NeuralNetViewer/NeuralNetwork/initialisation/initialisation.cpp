
#include "initialisation.h"

// He Initialization
Eigen::MatrixXf he_initialisation(int fan_in, int fan_out) {
    Eigen::MatrixXf weights(fan_out, fan_in);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0.0f, std::sqrt(2.0f / fan_in));

    for (int i = 0; i < weights.rows(); ++i)
        for (int j = 0; j < weights.cols(); ++j)
            weights(i, j) = dist(gen);

    return weights;
}

// Xavier Initialization
Eigen::MatrixXf xavier_initialisation(int fan_in, int fan_out) {
    Eigen::MatrixXf weights(fan_out, fan_in);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0.0f, std::sqrt(1.0f / fan_in));

    for (int i = 0; i < weights.rows(); ++i)
        for (int j = 0; j < weights.cols(); ++j)
            weights(i, j) = dist(gen);

    return weights;
}

// Normal (standard normal) Initialization
Eigen::MatrixXf normal_initialisation(int fan_in, int fan_out) {
    Eigen::MatrixXf weights(fan_out, fan_in);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0.0f, 1.0f);

    for (int i = 0; i < weights.rows(); ++i)
        for (int j = 0; j < weights.cols(); ++j)
            weights(i, j) = dist(gen);

    return weights;
}

// Uniform Initialization [-0.05, 0.05]
Eigen::MatrixXf uniform_initialisation(int fan_in, int fan_out) {
    Eigen::MatrixXf weights(fan_out, fan_in);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-0.05f, 0.05f);

    for (int i = 0; i < weights.rows(); ++i)
        for (int j = 0; j < weights.cols(); ++j)
            weights(i, j) = dist(gen);

    return weights;
}

// Zero Initialization
Eigen::MatrixXf zero_initialisation(int fan_in, int fan_out) {
    return Eigen::MatrixXf::Zero(fan_out, fan_in);
}

// Entry point
Eigen::MatrixXf get_weight_init(WeightInitialisationType type, int fan_in, int fan_out) {
    switch (type) {
    case WeightInitialisationType::He:
        return he_initialisation(fan_in, fan_out);
    case WeightInitialisationType::Xavier:
        return xavier_initialisation(fan_in, fan_out);
    case WeightInitialisationType::Normal:
        return normal_initialisation(fan_in, fan_out);
    case WeightInitialisationType::Uniform:
        return uniform_initialisation(fan_in, fan_out);
    case WeightInitialisationType::Zero:
        return zero_initialisation(fan_in, fan_out);
    default:
        throw std::runtime_error("Unsupported weight initialisation type.");
    }
}
