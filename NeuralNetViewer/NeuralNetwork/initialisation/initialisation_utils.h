
#ifndef INITIALISATION_UTILS_H
#define INITIALISATION_UTILS_H

#include <QString>
#include <stdexcept>

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
#endif // INITIALISATION_UTILS_H
