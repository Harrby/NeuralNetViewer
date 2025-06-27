
#ifndef GLOBALOPTIONSWIDGET_H
#define GLOBALOPTIONSWIDGET_H
#include<QFrame>
#include"valuecomboboxwidget.h"
#include"valuesliderwidget.h"



class GlobalOptionsWidget : public QFrame
{
    Q_OBJECT
public:
    GlobalOptionsWidget(QWidget *parent=nullptr);

private:
    ValueComboBoxWidget *m_cb_optimiser, *m_cb_loss_function;
    ValueSliderWidget *m_s_learning_rate, *m_s_epochs;
    QLabel *m_title;

};

#endif // GLOBALOPTIONSWIDGET_H
