
#include "neuralnetoptionsdata.h"

NeuralNetOptionsData::NeuralNetOptionsData(QObject *parent)
    : QObject(parent),
    optimiser(QString("SGD")),
    loss_function(QString("CCE")),
    learning_rate(0.1),
    epochs(200),
    layers({NeuralNetLayerData(), NeuralNetLayerData()})

{

}

int NeuralNetOptionsData::addLayer(){
    layers.append(NeuralNetLayerData());
    return layers.size()-1;
}

void NeuralNetOptionsData::removeLayer(){
    if (!layers.isEmpty()){
        layers.removeLast();
    }
}

// GETTER METHODS
QString NeuralNetOptionsData::getLossFunction(){
    return loss_function;
}

QString NeuralNetOptionsData::getOptimiser(){
    return optimiser;
}

double NeuralNetOptionsData::getLearningRate(){
    return learning_rate;
}

int NeuralNetOptionsData::getEpochs(){
    return epochs;
}

// GETTER METHOD - PER LAYER
NeuralNetLayerData NeuralNetOptionsData::getLayerData(int index){
    return layers.at(index);
}

bool NeuralNetOptionsData::isLayerActive(int index){
    return layers.at(index).active;
}

int NeuralNetOptionsData::getLayerNeurons(int index){
    return layers.at(index).neurons;
}

QString NeuralNetOptionsData::getLayerActivationFunction(int index){
    return layers.at(index).activation_function;
}

QString NeuralNetOptionsData::getLayerWeightInit(int index){
    return layers.at(index).weight_initialisation;
}

double NeuralNetOptionsData::getLayerDropoutRate(int index){
    return layers.at(index).dropout_rate;
};

double NeuralNetOptionsData::getLayerL1Regularisation(int index){
    return layers.at(index).l1_regularisation;
};

double NeuralNetOptionsData::getLayerL2Regularisation(int index){
    return layers.at(index).l2_regularisation;
};

// SETTER METHODS
void NeuralNetOptionsData::setLossFunction(QString new_loss_function){
    loss_function = new_loss_function;
}

void NeuralNetOptionsData::setOptimiser(QString new_optimiser){
    optimiser = new_optimiser;
}

void NeuralNetOptionsData::setLearningRate(double new_learning_rate){
    learning_rate = new_learning_rate;
}

void NeuralNetOptionsData:: setEpochs(int new_epochs){
    this->epochs = new_epochs;
}

//SETTER METHODS - PER LAYER
void NeuralNetOptionsData::setLayerActive(int index, bool active){
    layers[index].active = active;
}
void NeuralNetOptionsData::setLayerNeurons(int index, int neurons){
    layers[index].neurons = neurons;
}

void NeuralNetOptionsData::setLayerActivationFunction(int index, QString activation_function){
    layers[index].activation_function = activation_function;
}

void NeuralNetOptionsData::setLayerWeightInit(int index, QString weight_init){
    layers[index].weight_initialisation = weight_init;
}
void NeuralNetOptionsData::setLayerDropoutRate(int index, double dropout_rate){
    layers[index].dropout_rate = dropout_rate;
}

void NeuralNetOptionsData::setLayerL1Regularisation(int index, double l1_regularisation){
    layers[index].l1_regularisation = l1_regularisation;
}
void NeuralNetOptionsData::setLayerL2Regularisation(int index, double l2_regularisation){
    layers[index].l2_regularisation = l2_regularisation;
}
