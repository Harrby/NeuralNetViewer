
#ifndef OPTIMISER_UTILS_H
#define OPTIMISER_UTILS_H
#include <QString>
#include <stdexcept>
#include <QList>

enum class OptimiserType{
    SGD,
    MomentumSGD,
    RMSProp
};

namespace OptimiserUtils {

// enum → QString
inline QString toString(OptimiserType t)
{
    switch (t) {
    case OptimiserType::SGD:         return "SGD";
    case OptimiserType::MomentumSGD: return "MomentumSGD";
    case OptimiserType::RMSProp:     return "RMSProp";
    }
    return "Unknown";
}

// QString → enum
inline OptimiserType fromString(const QString& s)
{
    if (s == "SGD")         return OptimiserType::SGD;
    if (s == "MomentumSGD") return OptimiserType::MomentumSGD;
    if (s == "RMSProp")     return OptimiserType::RMSProp;
    throw std::invalid_argument("Invalid activation function: " + s.toStdString());
}

inline QStringList allOptimiserStrings()
{
    using T = OptimiserType;
    static constexpr T allTypes[] = {
        T::SGD, T::MomentumSGD, T::RMSProp
    };

    QStringList result;
    for (T t : allTypes) {
        result << toString(t);
    }
    return result;
}

}
#endif // OPTIMISER_UTILS_H
