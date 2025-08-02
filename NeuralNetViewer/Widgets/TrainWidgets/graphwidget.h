
#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QFrame>
#include "qcustomplot.h"


class GraphWidget : public QFrame
{
    Q_OBJECT
public:
    GraphWidget(QWidget* parent =nullptr);
    void update_training_loss_data(int epoch,  float training_loss);
    void update_validation_loss_data(int epoch, float validation_loss);
    void reset_view();
    void replot();

private:
    QCustomPlot* m_plot;
    void set_dummy_data();
};

#endif // GRAPHWIDGET_H
