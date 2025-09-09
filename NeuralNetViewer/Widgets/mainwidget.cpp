
#include "mainwidget.h"
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    m_network_config_widget(new NetworkConfigWidget),
    m_train_widget(new TrainWidget),
    m_mnist_user_output_widget(new MNISTUserOutputWidget),
    m_mnist_user_input_widget(new MNISTInputWidget),
    m_test_input_widget(new TestWidget),
    m_test_output_widget(new TestOutputWidget),
    m_network_options(new NeuralNetOptionsData(this)),
    m_neural_network(new NeuralNetwork(*m_network_options, this)),
    m_dataset_container(new DataSetContainer())
{
    m_dataset_container->loadMNSITDataSet();
    initialiseUI();

    m_network_config_widget->setMinimumWidth(500);
    m_train_widget->setFixedWidth(560);

    QHBoxLayout* mnist_user_layout = new QHBoxLayout;
    mnist_user_layout->addWidget(m_mnist_user_input_widget);
    mnist_user_layout->addWidget(m_mnist_user_output_widget);
    mnist_user_layout->setSpacing(0);
    mnist_user_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* testing_layout = new QHBoxLayout;
    testing_layout->addWidget(m_test_input_widget);
    testing_layout->addWidget(m_test_output_widget);
    testing_layout->setSpacing(0);
    testing_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* input_output_layout = new QVBoxLayout;
    input_output_layout->addLayout(testing_layout);
    input_output_layout->addLayout(mnist_user_layout);
    input_output_layout->setContentsMargins(0, 0, 0, 0);
    input_output_layout->setSpacing(0);



    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_network_config_widget);
    layout->addWidget(m_train_widget);
    layout->addLayout(input_output_layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_neural_network->initialise_network();

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
    connect(m_train_widget, &TrainWidget::trainButtonClicked, this, &MainWidget::trainNeuralNetwork);
    connect(m_train_widget, &TrainWidget::cancelButtonClicked, m_neural_network, &NeuralNetwork::requestCancel);

    connect(m_mnist_user_input_widget, &MNISTInputWidget::PredictionRequest, m_neural_network, &NeuralNetwork::predict);

    connect(m_test_input_widget, &TestWidget::testButtonClicked, this, &MainWidget::testNeuralNetwork);
    connect(m_test_input_widget, &TestWidget::cancelButtonClicked, m_neural_network, &NeuralNetwork::requestCancel);

    connect(m_neural_network, &NeuralNetwork::epochDataChanged, m_train_widget, &TrainWidget::setEpochTrainingData);
    connect(m_neural_network, &NeuralNetwork::predictionFinished, m_mnist_user_output_widget, &MNISTUserOutputWidget::setAttributes);
    connect(m_neural_network, &NeuralNetwork::batchSamplesFinished, this, &MainWidget::onTestBatchSamplesFinished);




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

void MainWidget::onTestBatchSamplesFinished(TestingBatchResults results){
    m_test_input_widget->setStatusData(results.status);
    m_test_output_widget->setOutputStats(results.stats);

}

void MainWidget::testNeuralNetwork(){
    m_test_output_widget->clear();

    QThread* thread = new QThread(this);
    NeuralNetworkTester* tester = new NeuralNetworkTester(m_neural_network, m_dataset_container->m_testing_features, m_dataset_container->m_testing_labels);
    tester->moveToThread(thread);

    connect(thread, &QThread::started, tester, &NeuralNetworkTester::run);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(tester, &NeuralNetworkTester::finished, thread, &QThread::quit);
    connect(tester, &NeuralNetworkTester::finished, tester, &QObject::deleteLater);

    thread->start();


}


void MainWidget::trainNeuralNetwork(){
    qDebug() << " started training";
    QThread* thread = new QThread(this);
    NeuralNetworkTrainer* trainer = new NeuralNetworkTrainer(m_neural_network, m_dataset_container->m_training_features, m_dataset_container->m_training_labels);
    trainer->moveToThread(thread);

    connect(thread, &QThread::started, trainer, &NeuralNetworkTrainer::run);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(trainer, &NeuralNetworkTrainer::finished, thread, &QThread::quit);
    connect(trainer, &NeuralNetworkTrainer::finished, trainer, &QObject::deleteLater);

    thread->start();

}

void MainWidget::initialiseUI(){
    m_network_config_widget->initialiseUI(m_network_options);
    m_train_widget->initialiseUIParameters(m_network_options->getBatchSize(), m_network_options->isShuffleEnabled(),
                                           m_network_options->isValidationEnabled(), m_network_options->getValidationSplit());
}
