
#include "denselayeroptions.h"

DenseLayerOptions::DenseLayerOptions(const NeuralNetLayerData& parameters, int id, QWidget* parent)
    : LayerOptions(parameters, id, parent),
    m_s_neurons(new ValueSliderWidget(QString("Neurons"), 2, 256, Slider::Linear, 254, this)),
    m_s_dropout_rate(new ValueSliderWidget(QString("Dropout Rate"), 0, 1, Slider::Linear, 1000, this))
{

    setStyleSheet(".DenseLayerOptions{background-color: #302B2B;"
                  "border: 1px solid #2A2626;"
                  "border-radius: 4px;}");

    initFromParameters(parameters);

    QHBoxLayout *h_layout = new QHBoxLayout;
    h_layout->addWidget(m_checkbox);
    h_layout->addWidget(m_title);


    QGridLayout *grid_layout = new QGridLayout;
    grid_layout->addWidget(m_s_neurons, 0, 0);
    grid_layout->addWidget(m_s_dropout_rate, 0, 1);
    grid_layout->addWidget(m_cb_activation_function, 1, 0);
    grid_layout->addWidget(m_s_l1_regularisation, 1, 1);
    grid_layout->addWidget(m_cb_weight_initialisation, 2, 0);
    grid_layout->addWidget(m_s_l2_regularisation, 2, 1);
    grid_layout->setVerticalSpacing(2);
    grid_layout->setHorizontalSpacing(18);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addLayout(h_layout);
    main_layout->addLayout(grid_layout);

    connect(m_s_neurons, &ValueSliderWidget::valueChanged, this,
            [this](double neurons){
                emit neuronsChanged(m_id, static_cast<int>(neurons));
            });

    connect(m_s_dropout_rate, &ValueSliderWidget::valueChanged, this,
            [this](double dropout_rate){
                emit dropoutRateChanged(m_id, dropout_rate);
            });

}

void DenseLayerOptions::initFromParameters(const NeuralNetLayerData& parameters){
    setActive(parameters.active);
    setNeurons(parameters.neurons);
    setDropoutRate(parameters.dropout_rate);
    setActivationFunction(parameters.activation_function);
    setWeightInit(parameters.weight_initialisation);
    setL1Regularisation(parameters.l1_regularisation);
    setL2Regularisation(parameters.l2_regularisation);
};


void DenseLayerOptions::setAllParameters(const NeuralNetLayerData& parameters){
    initFromParameters(parameters);

}

void DenseLayerOptions::setNeurons(int neurons){
    m_s_neurons->setValue(static_cast<double>(neurons));
}

void DenseLayerOptions::setDropoutRate(double dropout_rate){
    m_s_dropout_rate->setValue(dropout_rate);

}

void DenseLayerOptions::setAsFinalLayer(bool final){
    m_title->setText(QString("Output Layer"));
    setNeurons(10);
    emit activationFunctionChanged(m_id, ActivationFunctionType::Identity);
    m_s_neurons->setInteractive(!final);
    m_s_dropout_rate->setVisible(!final);
    m_cb_activation_function->setVisible(!final);


}




