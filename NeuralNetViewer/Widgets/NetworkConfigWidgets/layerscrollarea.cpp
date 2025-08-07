
#include "layerscrollarea.h"

LayerScrollArea::LayerScrollArea(QWidget* parent)
    : QScrollArea(parent),
    container(new QFrame()),
    layer_option_widgets(QVector<LayerOptions*>()),
    main_layout(new QVBoxLayout(container)),
    next_free_index(0)

{
    this->setFrameShape(QFrame::NoFrame);
    this->setWidgetResizable(true);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setStyleSheet(".LayerScrollArea{"
                        "background-color: rgb(105,108,109);"
                        "border 0px solid black;"
                        "}");
    container->setStyleSheet(".QFrame{"
                             "background-color: rgb(105,108,109);"
                             "}");

    main_layout->setSpacing(4);
    main_layout->setContentsMargins(0, 4, 0, 16);

    this->setWidget(container);


}

void LayerScrollArea::initialiseLayerOptionsWidgets(const NeuralNetOptionsData& parameters){
    // just inits two widgets with same parameters.
    for (int i=0 ; i < parameters.getLenLayers(); i++){
        addLayerOptionsWidget(parameters.getLayerData(i));
    }

}


void LayerScrollArea::addLayerOptionsWidget(const NeuralNetLayerData& parameters){
    LayerOptions* w = new LayerOptions(parameters, next_free_index, container);
    if (!layer_option_widgets.isEmpty()) {
        layer_option_widgets.last()->setAsFinalLayer(false);
        layer_option_widgets.last()->setNeurons(32);
    }
    w->setAsFinalLayer(true);

    w->setVisible(false);
    layer_option_widgets.append(w);
    main_layout->addWidget(w);
    next_free_index++;
    w->setVisible(true);

    connect(w, &LayerOptions::activeChanged, this, &LayerScrollArea::activeChanged);
    connect(w, &LayerOptions::neuronsChanged, this, &LayerScrollArea::neuronsChanged);
    connect(w, &LayerOptions::dropoutRateChanged, this, &LayerScrollArea::dropoutRateChanged);
    connect(w, &LayerOptions::activationFunctionChanged, this, &LayerScrollArea::activationFunctionChanged);
    connect(w, &LayerOptions::weightInitChanged, this, &LayerScrollArea::weightInitChanged);
    connect(w, &LayerOptions::l1RegularisationChanged, this, &LayerScrollArea::l1RegularisationChanged);
    connect(w, &LayerOptions::l2RegularisationChanged, this, &LayerScrollArea::l2RegularisationChanged);

}

void LayerScrollArea::removeLayerOptionsWidget(){
    if (next_free_index <= 0)
        return;




    container->setUpdatesEnabled(false);

    next_free_index--;
    LayerOptions* widget_to_remove = layer_option_widgets[next_free_index];
    widget_to_remove->hide();
    main_layout->removeWidget(widget_to_remove);
    layer_option_widgets.removeAt(next_free_index);
    widget_to_remove->deleteLater();
    main_layout->activate();
    container->updateGeometry();
    if (QWidget* cw = this->widget())
        cw->adjustSize();

    if (!layer_option_widgets.isEmpty()) {
        layer_option_widgets.last()->setAsFinalLayer(true);
    }

    container->setUpdatesEnabled(true);

}
