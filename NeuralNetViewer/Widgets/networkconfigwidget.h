
#ifndef NETWORKCONFIGWIDGET_H
#define NETWORKCONFIGWIDGET_H

#include <QFrame>
#include "globaloptionswidget.h"
#include "buttonsframe.h"
#include "layerscrollarea.h"



class NetworkConfigWidget : public QFrame
{
    Q_OBJECT
public:
    NetworkConfigWidget(QWidget* parent=nullptr);
    void addLayerWidget(const NeuralNetLayerData &parameters);
    void removeLayerWidget();

private:
    GlobalOptionsWidget* m_global_options_widget;
    ButtonsFrame* m_buttons_frame;
    LayerScrollArea* m_layer_scroll_area;


signals:
    void addLayerButtonClicked();
    void removeLayerButtonClicked();
};

#endif // NETWORKCONFIGWIDGET_H
