
#ifndef TRAINSTATUSWIDGET_H
#define TRAINSTATUSWIDGET_H

#include <QFrame>
#include "statusbar.h"
#include "trainingstatsframe.h"
#include "graphwidget.h"
#include <QLabel>
#include "logwidget.h"
#include "epochstats.h"



class TrainStatusWidget : public QFrame
{
    Q_OBJECT
public:
    TrainStatusWidget(QWidget* parent = nullptr);
    void setEpochTrainingData(const EpochStats& epoch_stats);
    void clearData();

private:
    QLabel* m_title_label;
    StatusBar* m_status_bar;

    TrainingStatsFrame* m_stats_frame;

    GraphWidget* m_graph_widget;
    QLabel* m_log_title_label;
    LogWidget* m_log_widget;

};

#endif // TRAINSTATUSWIDGET_H
