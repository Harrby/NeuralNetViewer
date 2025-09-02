
#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QWidget>
#include "networkconfigwidget.h"
#include <QSplitter>
#include "neuralnetoptionsdata.h"
#include "trainwidget.h"
#include "neuralnetwork.h"
#include "datasetcontainer.h"
#include "neuralnetworktrainer.h"
#include "mnistinputwidget.h"
#include "mnistuseroutputwidget.h"


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private:
    QSplitter* m_splitter;
    NetworkConfigWidget* m_network_config_widget;
    TrainWidget* m_train_widget;
    MNISTUserOutputWidget* m_mnist_user_output_widget;
    MNISTInputWidget* m_mnist_user_input_widget;


    NeuralNetOptionsData* m_network_options;
    NeuralNetwork* m_neural_network;
    DataSetContainer* m_dataset_container;

    void onAddLayerRequest();
    void onRemoveLayerRequest();
    void trainNeuralNetwork();
    void predictUserInput(Eigen::VectorXf inputs);
    void initialiseUI();

signals:

};

#endif // MAINWIDGET_H
