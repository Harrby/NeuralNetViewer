
#ifndef TESTINGBATCHRESULTS_H
#define TESTINGBATCHRESULTS_H

#include "testoutputstats.h"
#include "teststatusstats.h"
#include <QObject>




struct TestingBatchResults {
    TestOutputStats stats;
    TestStatusStats status;
};


#endif // TESTINGBATCHRESULTS_H
