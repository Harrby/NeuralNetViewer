
#ifndef MNISTINPUTWIDGET_H
#define MNISTINPUTWIDGET_H

#include <QFrame>
#include "drawarea.h"
#include "iconbutton.h"
#include "valuesliderwidget.h"

#include <QLabel>
#include <QHBoxLayout>


class MNISTInputWidget : public QFrame
{
    Q_OBJECT
public:
    MNISTInputWidget(QWidget* parent = nullptr);

private:
    DrawArea* m_draw_area;
    ValueSliderWidget* m_pen_width_slider;
    ValueSliderWidget* m_pen_spread_slider;
    IconButton* m_clear_button;
    IconButton* m_predict_button;

};

#endif // MNISTINPUTWIDGET_H
