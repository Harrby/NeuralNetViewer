
#ifndef NETWORKCONFIGWIDGET_H
#define NETWORKCONFIGWIDGET_H

#include <QFrame>
#include "globaloptionswidget.h"
#include "buttonsframe.h"
#include "layerscrollarea.h"
#include "neuralnetoptionsdata.h"



class NetworkConfigWidget : public QFrame
{
    Q_OBJECT
public:
    NetworkConfigWidget(QWidget* parent=nullptr);
    void addLayerWidget(const NeuralNetLayerData& parameters);
    void removeLayerWidget();
    void initialiseUI(const NeuralNetOptionsData& parameters);

private:
    GlobalOptionsWidget* m_global_options_widget;
    ButtonsFrame* m_buttons_frame;
    LayerScrollArea* m_layer_scroll_area;


signals:
    void addLayerButtonClicked();
    void removeLayerButtonClicked();

    void optimiserChanged(OptimiserType optimiser);
    void lossFunctionChanged(LossFunctionType loss_function);
    void learningRateChanged(float learning_rate);
    void epochsChanged(int epochs);

    void momentumChanged(double);
    void beta1Changed(double);
    void beta2Changed(double);


    void activeChanged(int, bool);
    void neuronsChanged(int, int);
    void dropoutRateChanged(int, double);
    void activationFunctionChanged(int, ActivationFunctionType);
    void weightInitChanged(int, WeightInitialisationType);
    void l1RegularisationChanged(int, double);
    void l2RegularisationChanged(int, double);
};

#endif // NETWORKCONFIGWIDGET_H
