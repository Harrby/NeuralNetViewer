
#include "globaloptionswidget.h"
#include "qgridlayout.h"
std::array<QString, 3> BUTTONCOLORS = {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"};
GlobalOptionsWidget::GlobalOptionsWidget(QWidget *parent)
    : QFrame(parent),
    m_cb_optimiser(new ValueComboBoxButtonWidget(":/images/images/settings_icon.png", BUTTONCOLORS,"Optimiser", OptimiserUtils::allOptimiserStrings(), this)),
    m_cb_loss_function(new ValueComboBoxWidget("Loss Function", QStringList{"CCE"}, this)),
    m_s_learning_rate(new ValueSliderWidget("Learning Rate", 1e-6, 1.0, Slider::Logarithmic, 1000, this)),
    m_s_epochs(new ValueSliderWidget("Epochs", 0, 400, Slider::Linear, 400, this)),
    m_title(new QLabel("Global Options", this)),
    m_optimiser_advanced_controls_widget(new OptimiserAdvancedControlsWidget(this))
{
    setMaximumHeight(275);

    m_cb_optimiser->toggle_enable_button(false);

    setObjectName("globalOptionsFrame");
    setStyleSheet("#globalOptionsFrame{background-color: #302B2B;"
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
    main_layout->addWidget(m_optimiser_advanced_controls_widget);

    connect(m_cb_optimiser, &ValueComboBoxButtonWidget::valueChanged, this,
            [this](const QString& optimiser_txt){
                OptimiserType optimiser = OptimiserUtils::fromString(optimiser_txt);
                m_cb_optimiser->toggle_enable_button(optimiser != OptimiserType::SGD);
                m_optimiser_advanced_controls_widget->setOptimiserOptions(optimiser);
                emit optimiserChanged(optimiser);
            });

    connect(m_cb_optimiser, &ValueComboBoxButtonWidget::buttonClicked, this,
            [this](){
                m_optimiser_advanced_controls_widget->toggle_visibility();
            });

    connect(m_cb_loss_function, &ValueComboBoxWidget::valueChanged, this,
            [this](const QString& loss_txt){
                emit lossFunctionChanged(LossFnUtils::fromString(loss_txt));
            });

    connect(m_s_learning_rate, &ValueSliderWidget::valueChanged, this, &GlobalOptionsWidget::learningRateChanged);
    connect(m_s_epochs, &ValueSliderWidget::valueChanged, this, [this](double epochs){
        emit epochsChanged(static_cast<int>(epochs));
    });


    connect(m_optimiser_advanced_controls_widget, &OptimiserAdvancedControlsWidget::momentumChanged, this, &GlobalOptionsWidget::momentumChanged);
    connect(m_optimiser_advanced_controls_widget, &OptimiserAdvancedControlsWidget::beta1Changed, this, &GlobalOptionsWidget::beta1Changed);
    connect(m_optimiser_advanced_controls_widget, &OptimiserAdvancedControlsWidget::beta2Changed, this, &GlobalOptionsWidget::beta2Changed);


}

void GlobalOptionsWidget::initialiseUIParameters(const NeuralNetOptionsData& parameters){
    m_cb_optimiser->setValue(OptimiserUtils::toString(parameters.getOptimiser()));
    m_cb_loss_function->setValue(LossFnUtils::toString(parameters.getLossFunction()));
    m_s_learning_rate->setValue(parameters.getLearningRate());
    m_s_epochs->setValue(parameters.getEpochs());
    m_optimiser_advanced_controls_widget->initialise_sliders(parameters.getMomentum(), parameters.getBeta1(), parameters.getBeta2());
};


