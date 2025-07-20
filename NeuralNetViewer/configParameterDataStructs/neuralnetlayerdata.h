
#ifndef NEURALNETLAYERDATA_H
#define NEURALNETLAYERDATA_H


#include <QString>
#include <stdexcept>

//Activation Function enums
enum class ActivationFunctionType {
    ReLU,
    LeakyReLU,
    Identity,
    Sigmoid,
    Tanh,
    Softmax
};

namespace ActivationFnUtils {

    // enum → QString
    inline QString toString(ActivationFunctionType t)
    {
        switch (t) {
        case ActivationFunctionType::ReLU:        return "ReLU";
        case ActivationFunctionType::LeakyReLU:   return "Leaky ReLU";
        case ActivationFunctionType::Identity:    return "ID";
        case ActivationFunctionType::Sigmoid:     return "Sigmoid";
        case ActivationFunctionType::Tanh:        return "Tanh";
        case ActivationFunctionType::Softmax:     return "Softmax";
        }
        return "Unknown";
    }

    // QString → enum
    inline ActivationFunctionType fromString(const QString& s)
    {
        if (s == "ReLU")        return ActivationFunctionType::ReLU;
        if (s == "Leaky ReLU")  return ActivationFunctionType::LeakyReLU;
        if (s == "ID")          return ActivationFunctionType::Identity;
        if (s == "Sigmoid")     return ActivationFunctionType::Sigmoid;
        if (s == "Tanh")        return ActivationFunctionType::Tanh;
        if (s == "Softmax")     return ActivationFunctionType::Softmax;
        throw std::invalid_argument("Invalid activation function: " + s.toStdString());
    }

}

// Weight Init enums
enum class WeightInitialisationType{
    He,
    Normal,
    Xavier
};

namespace WeightInitUtils {

    inline QString toString(WeightInitialisationType t)
    {
        switch (t) {
        case WeightInitialisationType::He:        return "He";
        case WeightInitialisationType::Normal:    return "Normal";
        case WeightInitialisationType::Xavier:    return "Xavier";
        }
        return "Unknown";
    }

    inline WeightInitialisationType fromString(const QString& s){
        if (s == "He")     return WeightInitialisationType::He;
        if (s == "Normal") return WeightInitialisationType::Normal;
        if (s == "Xavier") return WeightInitialisationType::Xavier;
        throw std::invalid_argument("Invalid Weight Init: " + s.toStdString());
    }
}

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
