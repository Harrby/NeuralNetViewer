
#ifndef LOSS_UTILS_H
#define LOSS_UTILS_H
#include <QString>
#include <stdexcept>
#include <QDebug>

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
#endif // LOSS_UTILS_H
