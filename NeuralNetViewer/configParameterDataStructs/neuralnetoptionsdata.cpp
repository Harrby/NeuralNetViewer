
#include "neuralnetoptionsdata.h"

NeuralNetOptionsData::NeuralNetOptionsData(QObject *parent)
    : QObject(parent),
    batch_size(10),
    shuffle_data(true),
    use_validation_set(true),
    validation_split(0.2f),
    optimiser(OptimiserType::SGD),
    loss_function(LossFunctionType::CategoricalCrossEntropy),
    learning_rate(0.1f),
    momentum(0.9f),
    beta1(0.9f),
    beta2(0.9f),
    epsilon(1e-8f),
    epochs(200),
    activation_functions {
            ActivationFunctionType::ReLU,
            ActivationFunctionType::Identity
    }


{
    layers.push_back(std::make_unique<NeuralNetLayerData>());
    layers.push_back(std::make_unique<NeuralNetLayerData>());

    layers[1]->activation_function = activation_functions[1];
}

int NeuralNetOptionsData::addLayer(){
    layers.insert(layers.end()-1, std::make_unique<NeuralNetLayerData>());
    activation_functions.insert(activation_functions.end()-1, layers.at(layers.size()-1)->activation_function);

    int index = static_cast<int>(layers.size() - 2);
    //layers[index]->activation_function

    return index;
}

void NeuralNetOptionsData::removeLayer(){
    if (layers.size() > 1){
        layers.pop_back();
    }
}

// GETTER METHODS

int NeuralNetOptionsData::getBatchSize() const{
    return batch_size;
}

bool NeuralNetOptionsData::isShuffleEnabled() const{
    return shuffle_data;
}
bool NeuralNetOptionsData::isValidationEnabled() const{
    return use_validation_set;
}
float NeuralNetOptionsData::getValidationSplit() const{
    return validation_split;
}

int NeuralNetOptionsData::getInputSize() const{
    return input_size;
}

LossFunctionType NeuralNetOptionsData::getLossFunction() const{
    return loss_function;
}


OptimiserType NeuralNetOptionsData::getOptimiser() const{
    return optimiser;
}

float NeuralNetOptionsData::getLearningRate() const{
    return learning_rate;
}

float NeuralNetOptionsData::getMomentum() const{
    return momentum;
};
float NeuralNetOptionsData::getBeta1() const{
    return beta1;
}
float NeuralNetOptionsData::getBeta2() const{
    return beta2;
}

float NeuralNetOptionsData::getEpsilon() const{
    return epsilon;
}

int NeuralNetOptionsData::getEpochs() const{
    return epochs;
}

int NeuralNetOptionsData::getLenLayers() const{
    return static_cast<int>(layers.size());
};

// GETTER METHOD - PER LAYER
NeuralNetLayerData NeuralNetOptionsData::getLayerData(int index) const{
     return *(layers.at(index)); // or layers.at(index)
}



bool NeuralNetOptionsData::isLayerActive(int index){
    return layers.at(index)->active;
}

int NeuralNetOptionsData::getLayerNeurons(int index){
    return layers.at(index)->neurons;
}

ActivationFunctionType NeuralNetOptionsData::getLayerActivationFunction(int index){
    return activation_functions[index];
}


float NeuralNetOptionsData::getLayerDropoutRate(int index){
    return layers.at(index)->dropout_rate;
};

float NeuralNetOptionsData::getLayerL1Regularisation(int index){
    return layers.at(index)->l1_regularisation;
};

float NeuralNetOptionsData::getLayerL2Regularisation(int index){
    return layers.at(index)->l2_regularisation;
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
void NeuralNetOptionsData::setValidationSplit(float validation_split){
    this->validation_split = validation_split;
}

void NeuralNetOptionsData::setInputSize(int input_size){
    this->input_size = input_size;
}

void NeuralNetOptionsData::setLossFunction(LossFunctionType new_loss_function){
    loss_function = new_loss_function;
}

void NeuralNetOptionsData::setOptimiser(OptimiserType new_optimiser){
    optimiser = new_optimiser;
}

void NeuralNetOptionsData::setLearningRate(float learning_rate){
    this->learning_rate = learning_rate;
}

void NeuralNetOptionsData::setMomentum(float momentum){
    this->momentum = momentum;
}
void NeuralNetOptionsData::setBeta1(float beta1){
    this->beta1 = beta1;
}
void NeuralNetOptionsData::setBeta2(float beta2){
    this->beta2 = beta2;
}
void NeuralNetOptionsData::setEpsilon(float epsilon){
    this->epsilon = epsilon;
}

void NeuralNetOptionsData:: setEpochs(int epochs){
    this->epochs = epochs;
}

//SETTER METHODS - PER LAYER
void NeuralNetOptionsData::setLayerActive(int index, bool active){
    layers[index]->active = active;
}
void NeuralNetOptionsData::setLayerNeurons(int index, int neurons){
    layers[index]->neurons = neurons;
}

void NeuralNetOptionsData::setLayerActivationFunction(int index, ActivationFunctionType activation_function){
    activation_functions[index] = activation_function;
    layers[index]->activation_function = activation_function;
}

void NeuralNetOptionsData::setLayerWeightInit(int index, WeightInitialisationType weight_init){
    layers[index]->weight_initialisation = weight_init;
}
void NeuralNetOptionsData::setLayerDropoutRate(int index, float dropout_rate){
    layers[index]->dropout_rate = dropout_rate;
}

void NeuralNetOptionsData::setLayerL1Regularisation(int index, float l1_regularisation){
    layers[index]->l1_regularisation = l1_regularisation;
}
void NeuralNetOptionsData::setLayerL2Regularisation(int index, float l2_regularisation){
    layers[index]->l2_regularisation = l2_regularisation;
}
