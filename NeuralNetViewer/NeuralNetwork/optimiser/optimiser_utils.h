
#ifndef OPTIMISER_UTILS_H
#define OPTIMISER_UTILS_H
#include <QString>
#include <stdexcept>

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
#endif // OPTIMISER_UTILS_H
