
#ifndef VALUESLIDERWIDGET_H
#define VALUESLIDERWIDGET_H
#include <QFrame>
#include <QLabel>
#include "slider.h"
#include "lineedit.h"



class ValueSliderWidget : public QFrame
{
    Q_OBJECT
public:
    ValueSliderWidget(const QString &labelText = QString(), double min_value=0, double max_value=100, Slider::Scale=Slider::Linear, int steps=100, QWidget *parent=nullptr);
private:
    Slider* m_slider;
    LineEdit* m_lineEdit;
    QLabel* m_label;

};

#endif // VALUESLIDERWIDGET_H
