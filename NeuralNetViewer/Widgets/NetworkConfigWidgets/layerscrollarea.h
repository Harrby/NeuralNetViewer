
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

signals:
    void activeChanged(int, bool);
    void neuronsChanged(int, int);
    void dropoutRateChanged(int, double);
    void activationFunctionChanged(int, ActivationFunctionType);
    void weightInitChanged(int, WeightInitialisationType);
    void l1RegularisationChanged(int, double);
    void l2RegularisationChanged(int, double);
};

#endif // LAYERSCROLLAREA_H
