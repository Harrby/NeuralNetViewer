
#ifndef TESTOUTPUTSTATS_H
#define TESTOUTPUTSTATS_H
#include "samplelogmessagestats.h"
#include <QVector>


struct TestOutputStats{
    float accuracy;
    float loss;
    QVector<SampleLogMessageStats> log_stats;

};

#endif // TESTOUTPUTSTATS_H
