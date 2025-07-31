
#include "mainwidget.h"
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    m_splitter(new QSplitter(Qt::Horizontal, this)),
    m_network_config_widget(new NetworkConfigWidget(m_splitter)),
    m_train_widget(new TrainWidget(m_splitter)),
    m_network_options(new NeuralNetOptionsData(this))
{


    QWidget* empty_space_container = new QWidget(m_splitter);
    empty_space_container->setStyleSheet("background-color: rgb(78, 78, 78); ");

    m_splitter->addWidget(m_network_config_widget);
    m_splitter->addWidget(m_train_widget);
    m_splitter->addWidget(empty_space_container);

    m_splitter->setStretchFactor(0, 5);
    m_splitter->setStretchFactor(1, 1);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_splitter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    connect(m_network_config_widget, &NetworkConfigWidget::addLayerButtonClicked, this, &MainWidget::onAddLayerRequest);
    connect(m_network_config_widget, &NetworkConfigWidget::removeLayerButtonClicked, this, &MainWidget::onRemoveLayerRequest);

    connect(m_network_config_widget, &NetworkConfigWidget::optimiserChanged, m_network_options, &NeuralNetOptionsData::setOptimiser);
    connect(m_network_config_widget, &NetworkConfigWidget::lossFunctionChanged, m_network_options, &NeuralNetOptionsData::setLossFunction);
    connect(m_network_config_widget, &NetworkConfigWidget::learningRateChanged, m_network_options, &NeuralNetOptionsData::setLearningRate);
    connect(m_network_config_widget, &NetworkConfigWidget::epochsChanged, m_network_options, &NeuralNetOptionsData::setEpochs);

    connect(m_network_config_widget, &NetworkConfigWidget::activeChanged, m_network_options, &NeuralNetOptionsData::setLayerActive);
    connect(m_network_config_widget, &NetworkConfigWidget::neuronsChanged, m_network_options, &NeuralNetOptionsData::setLayerNeurons);
    connect(m_network_config_widget, &NetworkConfigWidget::dropoutRateChanged, m_network_options, &NeuralNetOptionsData::setLayerDropoutRate);
    connect(m_network_config_widget, &NetworkConfigWidget::activationFunctionChanged, m_network_options, &NeuralNetOptionsData::setLayerActivationFunction);
    connect(m_network_config_widget, &NetworkConfigWidget::weightInitChanged, m_network_options, &NeuralNetOptionsData::setLayerWeightInit);
    connect(m_network_config_widget, &NetworkConfigWidget::l1RegularisationChanged, m_network_options, &NeuralNetOptionsData::setLayerL1Regularisation);
    connect(m_network_config_widget, &NetworkConfigWidget::l2RegularisationChanged, m_network_options, &NeuralNetOptionsData::setLayerL2Regularisation);

    connect(m_train_widget, &TrainWidget::batchSizeChanged, m_network_options, &NeuralNetOptionsData::setBatchSize);
    connect(m_train_widget, &TrainWidget::shuffleDataChanged, m_network_options, &NeuralNetOptionsData::setShuffleEnabled);
    connect(m_train_widget, &TrainWidget::useValidationSetChanged, m_network_options, &NeuralNetOptionsData::setValidationEnabled);
    connect(m_train_widget, &TrainWidget::validationSplitChanged, m_network_options, &NeuralNetOptionsData::setValidationSplit);




}

void MainWidget::onAddLayerRequest(){
    int index = m_network_options->addLayer();
    const NeuralNetLayerData& parameters = m_network_options->getLayerData(index);
    m_network_config_widget->addLayerWidget(parameters);
}

void MainWidget::onRemoveLayerRequest(){
    m_network_options->removeLayer();
    m_network_config_widget->removeLayerWidget();
}
