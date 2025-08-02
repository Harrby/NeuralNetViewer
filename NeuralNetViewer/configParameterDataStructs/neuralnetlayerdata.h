
#ifndef NEURALNETLAYERDATA_H
#define NEURALNETLAYERDATA_H


#include <QString>
#include <stdexcept>
#include "activation_utils.h"
#include "initialisation_utils.h"

class NeuralNetLayerData
{
public:
    NeuralNetLayerData();
    bool active = true;
    int neurons = 32;
    ActivationFunctionType activation_function = ActivationFunctionType::ReLU;
    WeightInitialisationType weight_initialisation = WeightInitialisationType::He;
    double dropout_rate = 0.0;
    double l1_regularisation = 0.0;
    double l2_regularisation = 0.0;
};


#endif // NEURALNETLAYERDATA_H
