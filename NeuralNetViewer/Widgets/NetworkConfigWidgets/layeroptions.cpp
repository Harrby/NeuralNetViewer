
#include "layeroptions.h"

LayerOptions::LayerOptions(const NeuralNetLayerData& parameters, int id, QWidget *parent)
    : QFrame(parent),
    m_id(id),
    m_title(new QLabel(QString("Layer %1").arg(id+1), this)),
    m_checkbox(new CheckBox(this)),
    m_cb_activation_function(new ValueComboBoxWidget(QString("Activation Function"), QStringList{"ReLu", "Leaky ReLU", "Tanh", "Sigmoid"}, this)),
    m_cb_weight_initialisation(new ValueComboBoxWidget(QString("Weight Initialisation"), QStringList{"He", "Xavier", "Normal"}, this)),
    m_s_neurons(new ValueSliderWidget(QString("Neurons"), 2, 256, Slider::Linear, 254, this)),
    m_s_dropout_rate(new ValueSliderWidget(QString("Dropout Rate"), 0, 1, Slider::Linear, 1000, this)),
    m_s_l1_regularisation(new ValueSliderWidget(QString("L1 Regularisation"), 1e-7, 0.01, Slider::Logarithmic, 1000, this)),
    m_s_l2_regularisation(new ValueSliderWidget(QString("L2 Regularisation"), 1e-6, 0.1, Slider::Logarithmic, 1000, this))
{
    setAllParameters(parameters);
    setStyleSheet(".LayerOptions{background-color: #302B2B;"
                  "border: 1px solid #2A2626;"
                  "border-radius: 4px;}");

    m_title->setStyleSheet("color: #ffffff;");


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


    connect(m_checkbox, &CheckBox::clicked, this,
            [this](bool active){
                emit activeChanged(m_id, active);
            });

    connect(m_s_neurons, &ValueSliderWidget::valueChanged, this,
            [this](double neurons){
                emit neuronsChanged(m_id, static_cast<int>(neurons));
            });

    connect(m_s_dropout_rate, &ValueSliderWidget::valueChanged, this,
            [this](double dropout_rate){
                emit dropoutRateChanged(m_id, dropout_rate);
            });

    connect(m_cb_activation_function, &ValueComboBoxWidget::valueChanged, this,
            [this](const QString& activation_txt){
                emit activationFunctionChanged(m_id, ActivationFnUtils::fromString(activation_txt));
            });

    connect(m_cb_weight_initialisation, &ValueComboBoxWidget::valueChanged, this,
            [this](const QString& weight_init_txt){
                emit weightInitChanged(m_id, WeightInitUtils::fromString(weight_init_txt));
            });

    connect(m_s_l1_regularisation, &ValueSliderWidget::valueChanged, this,
            [this](double l1_regularisation){
                emit l1RegularisationChanged(m_id, l1_regularisation);
            });

    connect(m_s_l2_regularisation, &ValueSliderWidget::valueChanged, this,
            [this](double l2_regularisation){
                emit l2RegularisationChanged(m_id, l2_regularisation);
            });



}

void LayerOptions::setAllParameters(const NeuralNetLayerData& parameters){
    setActive(parameters.active);
    setNeurons(parameters.neurons);
    setDropoutRate(parameters.dropout_rate);
    setActivationFunction(parameters.activation_function);
    setWeightInit(parameters.weight_initialisation);
    setL1Regularisation(parameters.l1_regularisation);
    setL2Regularisation(parameters.l2_regularisation);

}

void LayerOptions::setActive(bool active){
    m_checkbox->setChecked(active);
}

void LayerOptions::setNeurons(int neurons){
    m_s_neurons->setValue(static_cast<double>(neurons));
}

void LayerOptions::setDropoutRate(double dropout_rate){
    m_s_dropout_rate->setValue(dropout_rate);

}
void LayerOptions::setActivationFunction(ActivationFunctionType activation_function){

    m_cb_activation_function->setValue(ActivationFnUtils::toString(activation_function));
}

void LayerOptions::setWeightInit(WeightInitialisationType weight_init){

    m_cb_weight_initialisation->setValue(WeightInitUtils::toString(weight_init));

}
void LayerOptions::setL1Regularisation(double l1_regularisation){
    m_s_l1_regularisation->setValue(l1_regularisation);

}
void LayerOptions::setL2Regularisation(double l2_regularisation){
    m_s_l2_regularisation->setValue(l2_regularisation);

}

void LayerOptions::setAsFinalLayer(bool final){
    m_title->setText(QString("Output Layer"));
    setNeurons(10);
    emit activationFunctionChanged(m_id, ActivationFunctionType::Identity);
    m_s_neurons->setInteractive(!final);
    m_s_dropout_rate->setVisible(!final);
    m_cb_activation_function->setVisible(!final);


}













