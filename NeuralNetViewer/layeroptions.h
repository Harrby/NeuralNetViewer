
#ifndef LAYEROPTIONS_H
#define LAYEROPTIONS_H
#include <QFrame>
#include "checkbox.h"
#include "valuecomboboxwidget.h"
#include "valuesliderwidget.h"
#include <QGridLayout>


class LayerOptions : public QFrame
{
    Q_OBJECT
public:
    LayerOptions(int id=1, QWidget *parent=nullptr);
private:
    QLabel* m_title;
    CheckBox* m_checkbox;
    ValueComboBoxWidget* m_cb_activation_function;
    ValueComboBoxWidget* m_cb_weight_initialisation;
    ValueSliderWidget* m_s_neurons;
    ValueSliderWidget* m_s_dropout_rate;
    ValueSliderWidget* m_s_l1_regularisation;
    ValueSliderWidget* m_s_l2_regularisation;

};

#endif // LAYEROPTIONS_H
