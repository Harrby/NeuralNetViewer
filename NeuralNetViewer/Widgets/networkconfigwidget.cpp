
#include "networkconfigwidget.h"

NetworkConfigWidget::NetworkConfigWidget(QWidget* parent)
    : QFrame(parent),
    m_global_options_widget( new GlobalOptionsWidget(this)),
    m_buttons_frame(new ButtonsFrame(this)),
    m_layer_scroll_area( new LayerScrollArea(this))
{

    setStyleSheet(".NetworkConfigWidget{background-color: rgb(105, 108, 109);}");

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addWidget(m_global_options_widget);
    main_layout->addWidget(m_buttons_frame);
    main_layout->addWidget(m_layer_scroll_area);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);

    connect(m_buttons_frame, &ButtonsFrame::addButtonClicked, this, &NetworkConfigWidget::addLayerButtonClicked);
    connect(m_buttons_frame, &ButtonsFrame::removeButtonClicked, this, &NetworkConfigWidget::removeLayerButtonClicked);



}

void NetworkConfigWidget::addLayerWidget(const NeuralNetLayerData &parameters){
    m_layer_scroll_area->addLayerOptionsWidget(parameters);
}

void NetworkConfigWidget::removeLayerWidget(){
    m_layer_scroll_area->removeLayerOptionsWidget();
}

