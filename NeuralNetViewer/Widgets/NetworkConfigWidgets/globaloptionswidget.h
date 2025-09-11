
#ifndef GLOBALOPTIONSWIDGET_H
#define GLOBALOPTIONSWIDGET_H
#include<QFrame>
#include"valuecomboboxwidget.h"
#include"valuesliderwidget.h"
#include "optimiser_utils.h"
#include "loss_utils.h"
#include "valuecomboboxbuttonwidget.h"
#include "optimiseradvancedcontrolswidget.h"
#include "neuralnetoptionsdata.h"

class GlobalOptionsWidget : public QFrame
{
    Q_OBJECT
public:
    GlobalOptionsWidget(QWidget *parent=nullptr);
    void initialiseUIParameters(const NeuralNetOptionsData& parameters);

private:
    ValueComboBoxButtonWidget* m_cb_optimiser;
    ValueComboBoxWidget* m_cb_loss_function;
    ValueSliderWidget* m_s_learning_rate;
    ValueSliderWidget* m_s_epochs;
    QLabel* m_title;
    OptimiserAdvancedControlsWidget* m_optimiser_advanced_controls_widget;

    void optimiser_changed(QString optimiser_txt);

signals:
    void optimiserChanged(OptimiserType optimiser);
    void lossFunctionChanged(LossFunctionType loss_function);
    void learningRateChanged(double learning_rate);
    void epochsChanged(int epochs);

    void momentumChanged(double);
    void beta1Changed(double);
    void beta2Changed(double);


};

#endif // GLOBALOPTIONSWIDGET_H
