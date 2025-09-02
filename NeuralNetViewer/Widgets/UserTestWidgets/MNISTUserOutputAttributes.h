
#ifndef MNISTUSEROUTPUTATTRIBUTES_H
#define MNISTUSEROUTPUTATTRIBUTES_H


#include <Eigen/Dense>
#include <vector>

struct mnistOutputAttributes {
    int predictedClass;                        // e.g. 0–9
    float confidence;                          // e.g. max probability
    float entropy;                             // entropy of distribution
    std::vector<float> probabilities;          // size 10
    Eigen::VectorXf saliencies;                // length 784 (or Eigen::MatrixXf 28x28)
};

#endif // MNISTUSEROUTPUTATTRIBUTES_H
