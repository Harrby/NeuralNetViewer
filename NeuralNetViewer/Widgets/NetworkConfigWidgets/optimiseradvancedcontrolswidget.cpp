
#include "optimiseradvancedcontrolswidget.h"

OptimiserAdvancedControlsWidget::OptimiserAdvancedControlsWidget(QWidget* parent)
    :QFrame(parent),
    m_s_momentum(new ValueSliderWidget("Momentum", 0, 1, Slider::Linear, 100)),
    m_s_beta2_rms(new ValueSliderWidget("Beta 2", 0.5, 1, Slider::Linear, 500)),
    m_s_beta1(new ValueSliderWidget("Beta 1", 0.5, 1, Slider::Linear, 500)),
    m_s_beta2(new ValueSliderWidget("Beta 2", 0.9, 1, Slider::Linear, 1000)),
    m_s_beta1_k(new ValueSliderWidget("Beta 1", 0.5, 1, Slider::Linear, 500)),
    m_s_beta2_k(new ValueSliderWidget("Beta 2", 0.9, 1, Slider::Linear, 1000)),
    m_s_k(new ValueSliderWidget("K", 2, 6, Slider::Linear, 2)),
    m_stacked_widget(new QStackedWidget),
    m_main_layout(new QVBoxLayout)
{
    setFixedHeight(108);

    hide();

    QLabel* title = new QLabel("Advanced Optimiser Parameters");
    title->setStyleSheet("color: #ffffff;");
    QHBoxLayout* title_layout = new QHBoxLayout;
    title_layout->addStretch(1);
    title_layout->addWidget(title);
    title_layout->addStretch(1);
    title_layout->setContentsMargins(2, 4, 2, 0);

    QFrame* momentum_frame = new QFrame;
    QHBoxLayout* momentum_layout = new QHBoxLayout;
    momentum_layout->addWidget(m_s_momentum);
    momentum_layout->setContentsMargins(0, 0, 0, 0);
    momentum_frame->setLayout(momentum_layout);

    QFrame* rms_prop_frame = new QFrame;
    QHBoxLayout* rms_prop_layout = new QHBoxLayout;
    rms_prop_layout->addWidget(m_s_beta2_rms);
    rms_prop_layout->setContentsMargins(0, 0, 0, 0);
    rms_prop_frame->setLayout(rms_prop_layout);

    QFrame* adam_frame = new QFrame;
    QHBoxLayout* adam_layout = new QHBoxLayout;
    adam_layout->addWidget(m_s_beta1);
    adam_layout->addWidget(m_s_beta2);
    adam_layout->setContentsMargins(0, 0, 0, 0);
    adam_frame->setLayout(adam_layout);

    QFrame* hadam_frame = new QFrame;
    QGridLayout* hadam_layout = new QGridLayout;
    hadam_layout->addWidget(m_s_beta1_k, 0, 0);
    hadam_layout->addWidget(m_s_beta2_k, 0, 1);
    hadam_layout->addWidget(m_s_k, 1, 0);
    hadam_layout->setContentsMargins(0, 0, 0, 0);
    hadam_frame->setLayout(hadam_layout);


    m_stacked_widget->addWidget(momentum_frame);
    m_stacked_widget->addWidget(rms_prop_frame);
    m_stacked_widget->addWidget(adam_frame);
    m_stacked_widget->addWidget(hadam_frame);



    m_main_layout->setSpacing(0);
    m_main_layout->setContentsMargins(2, 2, 2, 2);
    m_main_layout->addStretch(1);
    m_main_layout->addLayout(title_layout);
    m_main_layout->addWidget(m_stacked_widget);
    setLayout(m_main_layout);

    connect(m_s_momentum, &ValueSliderWidget::valueChanged, this, &OptimiserAdvancedControlsWidget::momentumChanged);
    connect(m_s_beta2_rms, &ValueSliderWidget::valueChanged, this, &OptimiserAdvancedControlsWidget::beta2Changed);
    connect(m_s_beta1, &ValueSliderWidget::valueChanged, this, &OptimiserAdvancedControlsWidget::beta1Changed);
    connect(m_s_beta2, &ValueSliderWidget::valueChanged, this, &OptimiserAdvancedControlsWidget::beta2Changed);
    connect(m_s_beta1_k, &ValueSliderWidget::valueChanged, this, &OptimiserAdvancedControlsWidget::beta1Changed);
    connect(m_s_beta2_k, &ValueSliderWidget::valueChanged, this, &OptimiserAdvancedControlsWidget::beta2Changed);
    connect(m_s_k, &ValueSliderWidget::valueChanged, this, &OptimiserAdvancedControlsWidget::kChanged);
}

void OptimiserAdvancedControlsWidget::setOptimiserOptions(OptimiserType optimiser){
    setFixedHeight(86);
    switch(optimiser){
    case OptimiserType::SGD: setSGDOptimiserOptions(); break;
    case OptimiserType::MomentumSGD: m_stacked_widget->setCurrentIndex(0); break;
    case OptimiserType::RMSProp: m_stacked_widget->setCurrentIndex(1); break;
    case OptimiserType::Adamax:  m_stacked_widget->setCurrentIndex(2); break;
    case OptimiserType::HAdam: m_stacked_widget->setCurrentIndex(3);
                                setFixedHeight(150); break;
    case OptimiserType::Adam: m_stacked_widget->setCurrentIndex(2); break;
    }
}

void OptimiserAdvancedControlsWidget::setSGDOptimiserOptions(){
    hide();


}

void OptimiserAdvancedControlsWidget::toggle_visibility(){
    setUpdatesEnabled(false);
    m_main_layout->activate();
    updateGeometry();
    if (isVisible()) {
        hide();
    } else {
        show();
    }
    setUpdatesEnabled(true);
};

void OptimiserAdvancedControlsWidget::initialise_sliders(float momentum, float beta1, float beta2, int k){
    m_s_momentum->setValue(momentum);
    m_s_beta1->setValue(beta1);
    m_s_beta2->setValue(beta2);
    m_s_beta2_rms->setValue(beta2);
    m_s_beta1_k->setValue(beta1);
    m_s_beta2_k->setValue(beta2);
    m_s_k->setValue(static_cast<double>(k));
}


