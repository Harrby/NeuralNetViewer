
#ifndef NEURALNETOPTIONSDATA_H
#define NEURALNETOPTIONSDATA_H

#include <QString>
#include <QVector>
#include <QObject>
#include "neuralnetlayerdata.h"



class NeuralNetOptionsData : public QObject
{
    Q_OBJECT
public:
    NeuralNetOptionsData(QObject *parent=nullptr);

    int addLayer();
    void removeLayer();

    NeuralNetLayerData getLayerData(int index);
    bool isLayerActive(int index);
    int getLayerNeurons(int index);
    QString getLayerActivationFunction(int index);
    QString getLayerWeightInit(int index);
    double getLayerDropoutRate(int index);
    double getLayerL1Regularisation(int index);
    double getLayerL2Regularisation(int index);

    QString getOptimiser();
    QString getLossFunction();
    double getLearningRate();
    int getEpochs();

    void setLayerActive(int index, bool active);
    void setLayerNeurons(int index, int neurons);
    void setLayerActivationFunction(int index, QString activation_function);
    void setLayerWeightInit(int index, QString weight_init);
    void setLayerDropoutRate(int index, double Dropout_rate);
    void setLayerL1Regularisation(int index, double l1_regularisation);
    void setLayerL2Regularisation(int index, double l2_regularisation);


    void setOptimiser(QString new_optimiser);
    void setLossFunction(QString new_loss_function);
    void setLearningRate(double new_learning_rate);
    void setEpochs(int new_epochs);

private:
    QString optimiser;
    QString loss_function;
    double learning_rate;
    int     epochs;
    QVector<NeuralNetLayerData> layers;
};

#endif // NEURALNETOPTIONSDATA_H
