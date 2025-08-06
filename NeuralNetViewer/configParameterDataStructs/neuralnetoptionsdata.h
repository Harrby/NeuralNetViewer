
#ifndef NEURALNETOPTIONSDATA_H
#define NEURALNETOPTIONSDATA_H

#include <QString>
#include <QVector>
#include <QObject>
#include "neuralnetlayerdata.h"
#include "optimiser_utils.h"
#include "loss_utils.h"
#include "initialisation_utils.h"
#include "activation_utils.h"


class NeuralNetOptionsData : public QObject
{
    Q_OBJECT
public:
    NeuralNetOptionsData(QObject *parent=nullptr);

    int addLayer();
    void removeLayer();

    NeuralNetLayerData getLayerData(int index) const;

    int getLenLayers() const;
    bool isLayerActive(int index);
    int getLayerNeurons(int index);
    ActivationFunctionType getLayerActivationFunction(int index);
    WeightInitialisationType getLayerWeightInit(int index);
    double getLayerDropoutRate(int index);
    double getLayerL1Regularisation(int index);
    double getLayerL2Regularisation(int index);

    int getBatchSize() const;
    bool isShuffleEnabled() const;
    bool isValidationEnabled() const;
    double getValidationSplit() const;
    int getInputSize() const;
    OptimiserType getOptimiser() const;
    LossFunctionType getLossFunction() const;
    double getLearningRate() const;
    int getEpochs() const;

    void setLayerActive(int index, bool active);
    void setLayerNeurons(int index, int neurons);
    void setLayerActivationFunction(int index, ActivationFunctionType activation_function);
    void setLayerWeightInit(int index, WeightInitialisationType weight_init);
    void setLayerDropoutRate(int index, double Dropout_rate);
    void setLayerL1Regularisation(int index, double l1_regularisation);
    void setLayerL2Regularisation(int index, double l2_regularisation);

    void setBatchSize(int batch_size);
    void setShuffleEnabled(bool shuffle);
    void setValidationEnabled(bool validation);
    void setValidationSplit(double validation_split);
    void setInputSize(int input_size);
    void setOptimiser(OptimiserType new_optimiser);
    void setLossFunction(LossFunctionType new_loss_function);
    void setLearningRate(double new_learning_rate);
    void setEpochs(int new_epochs);

private:
    int batch_size;
    bool shuffle_data;
    bool use_validation_set;
    double validation_split;
    int input_size=784;

    OptimiserType optimiser;
    LossFunctionType loss_function;
    double learning_rate;
    int     epochs;
    std::vector<std::unique_ptr<NeuralNetLayerData>> layers;
    std::vector<ActivationFunctionType> activation_functions;
};

#endif // NEURALNETOPTIONSDATA_H
