
#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QWidget>
#include "networkconfigwidget.h"
#include <QSplitter>
#include "neuralnetoptionsdata.h"
#include "trainwidget.h"


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private:
    QSplitter* m_splitter;
    NetworkConfigWidget* m_network_config_widget;
    TrainWidget* m_train_widget;
    NeuralNetOptionsData* m_network_options;
    void onAddLayerRequest();
    void onRemoveLayerRequest();

signals:

};

#endif // MAINWIDGET_H
