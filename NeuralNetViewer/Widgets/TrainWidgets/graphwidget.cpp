
#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget* parent)
    :QFrame(parent),
    m_plot(new QCustomPlot(this))
{

    setStyleSheet("QFrame {"
                  " border: 2px solid black;"
                  " border-radius: 4px;"
                  "}");

    m_plot->setStyleSheet("QWidget {"
                          " border: 0px solid red;"
                          " border-radius: 4px;"
                          "}");

    m_plot->addGraph();

    m_plot->addGraph();

    m_plot->graph(0)->setPen(QPen(QColor(31, 161, 227), 2));
    m_plot->graph(0)->setName("Training Loss");
    m_plot->graph(1)->setPen(QPen(QColor(217, 217, 217), 2, Qt::DashLine));
    m_plot->graph(1)->setName("Validation Loss");

    m_plot->legend->setVisible(true);
    m_plot->legend->setBrush(QColor(0, 0, 0, 0));
    m_plot->legend->setTextColor(Qt::white);

    m_plot->xAxis->setLabel("Epoch");
    m_plot->yAxis->setLabel("Loss");

    m_plot->setInteractions(
        QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables
        );

    m_plot->xAxis->setLabelColor(Qt::white);
    m_plot->yAxis->setLabelColor(Qt::white);
    m_plot->xAxis->setTickLabelColor(Qt::white);
    m_plot->yAxis->setTickLabelColor(Qt::white);
    m_plot->xAxis->setBasePen(QPen(Qt::white));
    m_plot->yAxis->setBasePen(QPen(Qt::white));
    m_plot->xAxis->setTickPen(QPen(Qt::white));
    m_plot->yAxis->setTickPen(QPen(Qt::white));
    m_plot->xAxis->setSubTickPen(QPen(Qt::white));
    m_plot->yAxis->setSubTickPen(QPen(Qt::white));
    m_plot->xAxis->grid()->setPen(QPen(Qt::white, 0.2));
    m_plot->yAxis->grid()->setPen(QPen(Qt::white, 0.2));
    m_plot->xAxis->grid()->setSubGridPen(QPen(Qt::white, 0.1));
    m_plot->yAxis->grid()->setSubGridPen(QPen(Qt::white, 0.1));
    m_plot->xAxis->grid()->setSubGridVisible(true);
    m_plot->yAxis->grid()->setSubGridVisible(true);

    // Background color
    m_plot->setBackground(QBrush(Qt::black));

    m_plot->rescaleAxes();
    m_plot->replot();

    QHBoxLayout* main_layout = new QHBoxLayout(this);
    main_layout->addWidget(m_plot);
    main_layout->setContentsMargins(0, 0, 0, 0);

}

void GraphWidget::set_dummy_data(){
    QVector<double> x(100), y(100), y1(100);
    for (int i = 0; i < 100; ++i) {
        x[i] = i;
        y[i] = std::max(0.0, qExp(-i / 20.0) + (rand() % 100 - 50) / 500.0);
        y1[i] = std::max(0.0, qExp(-i/19.0) + (rand() % 100 -50) / 500.0);
    }



    m_plot->graph(0)->setData(x, y);
    m_plot->graph(1)->setData(x, y1);

}

void GraphWidget::reset_view(){
    m_plot->rescaleAxes();
    m_plot->replot();
}

void GraphWidget::update_training_loss_data(int epoch,  float training_loss){
    qDebug() << "plotted training data with " << epoch << training_loss;
    m_plot->graph(0)->addData(epoch, training_loss);

}
void GraphWidget::update_validation_loss_data(int epoch, float validation_loss){
    m_plot->graph(1)->addData(epoch, validation_loss);

}

void GraphWidget::replot(){
    m_plot->replot();
}

void GraphWidget::clear(){
    m_plot->graph(0)->data()->clear();
    m_plot->graph(1)->data()->clear();
    replot();
}

