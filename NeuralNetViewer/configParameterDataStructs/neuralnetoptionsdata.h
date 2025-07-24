
#ifndef NEURALNETOPTIONSDATA_H
#define NEURALNETOPTIONSDATA_H

#include <QString>
#include <QVector>
#include <QObject>
#include "neuralnetlayerdata.h"


enum class LossFunctionType{
    CategoricalCrossEntropy
};

namespace LossFnUtils {

// enum → QString
inline QString toString(LossFunctionType t)
{
    switch (t) {
    case LossFunctionType::CategoricalCrossEntropy:        return "Categorical Cross Entropy";
    }
    return "Unknown";
}

// QString → enum
inline LossFunctionType fromString(const QString& s)
{
    if (s == "Categorical Cross Entropy")        return LossFunctionType::CategoricalCrossEntropy;
    throw std::invalid_argument("Invalid activation function: " + s.toStdString());
}

}

enum class OptimiserType{
    SGD
};

namespace OptimiserUtils {

// enum → QString
inline QString toString(OptimiserType t)
{
    switch (t) {
    case OptimiserType::SGD:        return "SGD";
    }
    return "Unknown";
}

// QString → enum
inline OptimiserType fromString(const QString& s)
{
    if (s == "SGD")        return OptimiserType::SGD;
    throw std::invalid_argument("Invalid activation function: " + s.toStdString());
}

}


class NeuralNetOptionsData : public QObject
{
    Q_OBJECT
public:
    NeuralNetOptionsData(QObject *parent=nullptr);

    int addLayer();
    void removeLayer();

    NeuralNetLayerData getLayerData(int index);
    int getLenLayers();
    bool isLayerActive(int index);
    int getLayerNeurons(int index);
    ActivationFunctionType getLayerActivationFunction(int index);
    WeightInitialisationType getLayerWeightInit(int index);
    double getLayerDropoutRate(int index);
    double getLayerL1Regularisation(int index);
    double getLayerL2Regularisation(int index);

    int getBatchSize();
    OptimiserType getOptimiser();
    LossFunctionType getLossFunction();
    double getLearningRate();
    int getEpochs();

    void setLayerActive(int index, bool active);
    void setLayerNeurons(int index, int neurons);
    void setLayerActivationFunction(int index, ActivationFunctionType activation_function);
    void setLayerWeightInit(int index, WeightInitialisationType weight_init);
    void setLayerDropoutRate(int index, double Dropout_rate);
    void setLayerL1Regularisation(int index, double l1_regularisation);
    void setLayerL2Regularisation(int index, double l2_regularisation);


    void setOptimiser(OptimiserType new_optimiser);
    void setLossFunction(LossFunctionType new_loss_function);
    void setLearningRate(double new_learning_rate);
    void setEpochs(int new_epochs);

private:
    int batch_size;
    OptimiserType optimiser;
    LossFunctionType loss_function;
    double learning_rate;
    int     epochs;
    QVector<NeuralNetLayerData> layers;
};

#endif // NEURALNETOPTIONSDATA_H
