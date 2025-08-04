
#ifndef INITIALISATION_H
#define INITIALISATION_H

#include <Eigen/Dense>
#include <random>
#include <stdexcept>
#include <cmath>
#include "initialisation_utils.h"


Eigen::MatrixXf get_weight_init(WeightInitialisationType type, int fan_in, int fan_out);

#endif // INITIALISATION_H
