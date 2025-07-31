
#include "neuralnetoptionsdata.h"

NeuralNetOptionsData::NeuralNetOptionsData(QObject *parent)
    : QObject(parent),
    batch_size(10),
    shuffle_data(true),
    use_validation_set(true),
    validation_split(0.2),
    optimiser(OptimiserType::SGD),
    loss_function(LossFunctionType::CategoricalCrossEntropy),
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

int NeuralNetOptionsData::getBatchSize(){
    return batch_size;
}

bool NeuralNetOptionsData::isShuffleEnabled(){
    return shuffle_data;
}
bool NeuralNetOptionsData::isValidationEnabled(){
    return use_validation_set;
}
double NeuralNetOptionsData::getValidationSplit(){
    return validation_split;
}

LossFunctionType NeuralNetOptionsData::getLossFunction(){
    return loss_function;
}


OptimiserType NeuralNetOptionsData::getOptimiser(){
    return optimiser;
}

double NeuralNetOptionsData::getLearningRate(){
    return learning_rate;
}

int NeuralNetOptionsData::getEpochs(){
    return epochs;
}

int NeuralNetOptionsData::getLenLayers(){
    return layers.length();
};

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

ActivationFunctionType NeuralNetOptionsData::getLayerActivationFunction(int index){
    return layers.at(index).activation_function;
}

WeightInitialisationType NeuralNetOptionsData::getLayerWeightInit(int index){
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
void NeuralNetOptionsData::setBatchSize(int batch_size){
    this->batch_size = batch_size;
}
void NeuralNetOptionsData::setShuffleEnabled(bool shuffle){
    shuffle_data = shuffle;
}
void NeuralNetOptionsData::setValidationEnabled(bool validation){
    use_validation_set = validation;
}
void NeuralNetOptionsData::setValidationSplit(double validation_split){
    this->validation_split = validation_split;
}

void NeuralNetOptionsData::setLossFunction(LossFunctionType new_loss_function){
    loss_function = new_loss_function;
}

void NeuralNetOptionsData::setOptimiser(OptimiserType new_optimiser){
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

void NeuralNetOptionsData::setLayerActivationFunction(int index, ActivationFunctionType activation_function){
    layers[index].activation_function = activation_function;
}

void NeuralNetOptionsData::setLayerWeightInit(int index, WeightInitialisationType weight_init){
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
