
#ifndef NEURALNETLAYERDATA_H
#define NEURALNETLAYERDATA_H


#include <QString>

class NeuralNetLayerData
{
public:
    NeuralNetLayerData();
    bool active = true;
    int neurons = 32;
    QString activation_function = QString("ReLU");
    QString weight_initialisation = QString("He");
    double dropout_rate = 0.0;
    double l1_regularisation = 0.0;
    double l2_regularisation = 0.0;
};

#endif // NEURALNETLAYERDATA_H
