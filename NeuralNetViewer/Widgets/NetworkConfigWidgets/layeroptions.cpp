
#include "layeroptions.h"

LayerOptions::LayerOptions(const NeuralNetLayerData& parameters, int id, QWidget *parent)
    : QFrame(parent),
    m_id(id),
    m_title(new QLabel(QString("Layer %1").arg(id+1), this)),
    m_checkbox(new CheckBox(this)),
    m_cb_activation_function(new ValueComboBoxWidget(QString("Activation Function"), ActivationFnUtils::allActivationFunctionStrings(), this)),
    m_cb_weight_initialisation(new ValueComboBoxWidget(QString("Weight Initialisation"), WeightInitUtils::allWeightInitStrings(), this)),
    m_s_l1_regularisation(new ValueSliderWidget(QString("L1 Regularisation"), 1e-7, 0.01, Slider::Logarithmic, 5000, this)),
    m_s_l2_regularisation(new ValueSliderWidget(QString("L2 Regularisation"), 1e-6, 0.1, Slider::Logarithmic, 5000, this))
{
    setStyleSheet(".LayerOptions{background-color: #302B2B;"
                  "border: 1px solid #2A2626;"
                  "border-radius: 4px;}");

    m_title->setStyleSheet("color: #ffffff;");





    connect(m_checkbox, &CheckBox::clicked, this,
            [this](bool active){
                emit activeChanged(m_id, active);
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
    setActivationFunction(parameters.activation_function);
    setWeightInit(parameters.weight_initialisation);
    setL1Regularisation(parameters.l1_regularisation);
    setL2Regularisation(parameters.l2_regularisation);

}

void LayerOptions::setActive(bool active){
    m_checkbox->setChecked(active);
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














