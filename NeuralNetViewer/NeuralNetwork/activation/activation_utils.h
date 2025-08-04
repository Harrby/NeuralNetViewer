
#ifndef ACTIVATION_UTILS_H
#define ACTIVATION_UTILS_H
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


#endif // ACTIVATION_UTILS_H
