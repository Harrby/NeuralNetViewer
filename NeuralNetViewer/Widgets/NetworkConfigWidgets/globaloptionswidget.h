
#ifndef GLOBALOPTIONSWIDGET_H
#define GLOBALOPTIONSWIDGET_H
#include<QFrame>
#include"valuecomboboxwidget.h"
#include"valuesliderwidget.h"
#include "optimiser_utils.h"
#include "loss_utils.h"

class GlobalOptionsWidget : public QFrame
{
    Q_OBJECT
public:
    GlobalOptionsWidget(QWidget *parent=nullptr);
    void initialiseUIParameters(OptimiserType optimiser, LossFunctionType loss_function, double learning_rate, int epochs);

private:
    ValueComboBoxWidget* m_cb_optimiser;
    ValueComboBoxWidget* m_cb_loss_function;
    ValueSliderWidget* m_s_learning_rate;
    ValueSliderWidget* m_s_epochs;
    QLabel* m_title;
    void optimiser_changed(QString optimiser_txt);

signals:
    void optimiserChanged(OptimiserType optimiser);
    void lossFunctionChanged(LossFunctionType loss_function);
    void learningRateChanged(double learning_rate);
    void epochsChanged(int epochs);

};

#endif // GLOBALOPTIONSWIDGET_H
