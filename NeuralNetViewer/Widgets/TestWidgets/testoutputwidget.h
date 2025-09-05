
#ifndef TESTOUTPUTWIDGET_H
#define TESTOUTPUTWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QObject>
#include <QHBoxLayout>
#include "logwidget.h"
#include "testoutputstats.h"


class TestOutputWidget : public QFrame
{
    Q_OBJECT
public:
    TestOutputWidget(QWidget* parent = nullptr);
    void setOutputStats(TestOutputStats& stats);
    void clear();

private:
    QLabel* m_accuracy_label;
    QLabel* m_loss_label;
    LogWidget* m_log_widget;
};

#endif // TESTOUTPUTWIDGET_H
