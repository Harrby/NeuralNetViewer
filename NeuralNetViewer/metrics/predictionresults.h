
#ifndef PREDICTIONRESULTS_H
#define PREDICTIONRESULTS_H

#include <Eigen/Dense>
#include <vector>

struct PredictionResults {
    int predictedClass;                        // e.g. 0–9
    float confidence;                          // e.g. max probability
    float entropy;                             // entropy of distribution
    Eigen::VectorXf probabilities;          // size 10
    Eigen::VectorXf saliencies;                // length 784 (or Eigen::MatrixXf 28x28)
};

#endif // PREDICTIONRESULTS_H
