
#include "layeroptions.h"

LayerOptions::LayerOptions(int id,QWidget *parent)
    : QFrame(parent),
    m_title(new QLabel(QString("Layer %1").arg(id), this)),
    m_checkbox(new CheckBox(this)),
    m_cb_activation_function(new ValueComboBoxWidget(QString("Activation Function"), QStringList{"ReLu", "Leaky ReLU", "Tanh", "Sigmoid"}, this)),
    m_cb_weight_initialisation(new ValueComboBoxWidget(QString("Weight Initialisation"), QStringList{"He", "Xavier", "Normal"}, this)),
    m_s_neurons(new ValueSliderWidget(QString("Neurons"), 2, 256, Slider::Linear, 254, this)),
    m_s_dropout_rate(new ValueSliderWidget(QString("Dropout Rate"), 0, 1, Slider::Linear, 1000, this)),
    m_s_l1_regularisation(new ValueSliderWidget(QString("L1 Regularisation"), 1e-7, 0.01, Slider::Logarithmic, 1000, this)),
    m_s_l2_regularisation(new ValueSliderWidget(QString("L2 Regularisation"), 1e-6, 0.1, Slider::Logarithmic, 1000, this))
{
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
}

