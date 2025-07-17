
#include "mainwidget.h"
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    m_splitter(new QSplitter(Qt::Horizontal, this)),
    m_network_config_widget(new NetworkConfigWidget(m_splitter)),
    m_network_options(new NeuralNetOptionsData(this))
{


    QWidget* empty_space_container = new QWidget(m_splitter);
    empty_space_container->setStyleSheet("background-color: rgb(78, 78, 78); ");

    m_splitter->addWidget(empty_space_container);
    m_splitter->addWidget(m_network_config_widget);

    m_splitter->setStretchFactor(0, 5);
    m_splitter->setStretchFactor(1, 1);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_splitter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    connect(m_network_config_widget, &NetworkConfigWidget::addLayerButtonClicked, this, &MainWidget::onAddLayerRequest);
    connect(m_network_config_widget, &NetworkConfigWidget::removeLayerButtonClicked, this, &MainWidget::onRemoveLayerRequest);


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
