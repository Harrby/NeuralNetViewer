
#include "globaloptionswidget.h"
#include "qgridlayout.h"

GlobalOptionsWidget::GlobalOptionsWidget(QWidget *parent)
    : QFrame(parent),
    m_cb_optimiser(new ValueComboBoxWidget("Optimiser", OptimiserUtils::allOptimiserStrings(), this)),
    m_cb_loss_function(new ValueComboBoxWidget("Loss Function", QStringList{"CCE"}, this)),
    m_s_learning_rate(new ValueSliderWidget("Learning Rate", 1e-6, 1.0, Slider::Logarithmic, 1000, this)),
    m_s_epochs(new ValueSliderWidget("Epochs", 0, 1000, Slider::Linear, 1000, this)),
    m_title(new QLabel("Global Options", this))
{
    setStyleSheet(".GlobalOptionsWidget{background-color: #302B2B;"
                  "                     border 1px solid #2A2626;"
                  "                     border-radius:4px; }"
                  );

    m_title->setStyleSheet("color: white;");


    QGridLayout *grid_layout = new QGridLayout;
    grid_layout->addWidget(m_cb_optimiser, 0, 0);
    grid_layout->addWidget(m_cb_loss_function, 0, 1);
    grid_layout->addWidget(m_s_learning_rate, 1, 0);
    grid_layout->addWidget(m_s_epochs, 1, 1);
    grid_layout->setVerticalSpacing(0);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(m_title);
    main_layout->addLayout(grid_layout);

    connect(m_cb_optimiser, &ValueComboBoxWidget::valueChanged, this,
            [this](const QString& optimiser_txt){
                emit optimiserChanged(OptimiserUtils::fromString(optimiser_txt));
            });

    connect(m_cb_loss_function, &ValueComboBoxWidget::valueChanged, this,
            [this](const QString& loss_txt){
                emit lossFunctionChanged(LossFnUtils::fromString(loss_txt));
            });

    connect(m_s_learning_rate, &ValueSliderWidget::valueChanged, this, &GlobalOptionsWidget::learningRateChanged);
    connect(m_s_epochs, &ValueSliderWidget::valueChanged, this, [this](double epochs){
        emit epochsChanged(static_cast<int>(epochs));
    });

}

void GlobalOptionsWidget::initialiseUIParameters(OptimiserType optimiser, LossFunctionType loss_function, double learning_rate, int epochs){
    m_cb_optimiser->setValue(OptimiserUtils::toString(optimiser));
    m_cb_loss_function->setValue(LossFnUtils::toString(loss_function));
    m_s_learning_rate->setValue(learning_rate);
    m_s_epochs->setValue(epochs);
};


