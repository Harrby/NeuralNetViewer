
#ifndef EPOCHSTATS_H
#define EPOCHSTATS_H
#include <QDebug>

struct EpochStats {
    int epoch;
    int total_epochs;
    float training_loss;
    float validation_loss;
    float training_accuracy;
    float validation_accuracy;
    float eta;
};
QDebug operator<<(QDebug dbg, const EpochStats& stats);

#endif // EPOCHSTATS_H
