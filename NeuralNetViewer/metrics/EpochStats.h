
#ifndef EPOCHSTATS_H
#define EPOCHSTATS_H
struct EpochStats {
    int epoch;
    int total_epochs;
    float training_loss;
    float validation_loss;
    float training_accuracy;
    float validation_accuracy;
    float eta;
};
#endif // EPOCHSTATS_H
