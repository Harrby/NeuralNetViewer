
#ifndef LAYERSCROLLAREA_H
#define LAYERSCROLLAREA_H

#include <QFrame>
#include <QScrollArea>
#include <QVector>
#include "layeroptions.h"

class LayerScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    LayerScrollArea(QWidget *parent=nullptr);
    void initialiseLayerOptionsWidgets(const NeuralNetLayerData& parameters);
    void addLayerOptionsWidget(const NeuralNetLayerData& parameters);
    void removeLayerOptionsWidget();

private:
    QFrame* container;
    QVector<LayerOptions*> layer_option_widgets;
    QVBoxLayout* main_layout;
    int next_free_index;
};

#endif // LAYERSCROLLAREA_H
