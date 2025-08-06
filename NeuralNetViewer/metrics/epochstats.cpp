

#include "epochstats.h"

QDebug operator<<(QDebug dbg, const EpochStats& stats) {
    QDebugStateSaver save (dbg);
    dbg.nospace() << "EpochStats("
                  << "epoch=" << stats.epoch << "/"
                  << stats.total_epochs
                  << ", train_loss=" << stats.training_loss
                  << ", val_loss=" << stats.validation_loss
                  << ", train_acc=" << stats.training_accuracy
                  << ", val_acc=" << stats.validation_accuracy
                  << ", eta=" << stats.eta
                  << ")";
    return dbg;
}

