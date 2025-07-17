
#include "slider.h"
#include <QtMath>


Slider::Slider(Qt::Orientation orientation, double rmin, double rmax,
               Scale scale, int steps, QWidget* parent)
    : QSlider(orientation, parent),
    m_rmin(rmin), m_rmax(rmax), m_scale(scale)
{
    Q_ASSERT(rmax > rmin);
    if (scale == Logarithmic)
        Q_ASSERT(rmin > 0.0);             // ordinary log needs positive min

    /* integer range 0 … steps */
    setRange(0, steps);
    setSingleStep(1);

    connect(this, &QSlider::valueChanged, this, [&](int i){
        emit realValueChanged(fromSlider(i));
    });



    setMinimumWidth(100);
    setFixedHeight(18);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);  // enable hover events

    setStyleSheet(R"(

    QSlider {
        height: 18px;   /* raise the widget’s thickness */
    }




    QSlider::groove:horizontal {
        height: 4px;
        background: #d9d9d9;
        border-radius: 1px;
    }
    QSlider::handle:horizontal {
        width: 10px;
        height: 18px;
        background: #d9d9d9;
        border: 0px solid #3498db;
        border-radius: 2px;
        margin: -7px 0; /* center handle vertically */
    }

)");



}

double Slider::fromSlider(int i) const
{
    double t = double(i - minimum()) / (maximum() - minimum());     // 0 … 1

    if (m_scale == Linear)
        return m_rmin + t * (m_rmax - m_rmin);                      // lerp
    else
        return m_rmin * qPow(m_rmax / m_rmin, t);                   // log-interp
}

int Slider::toSlider(double r) const
{
    r = qBound(m_rmin, r, m_rmax);

    double t = (m_scale == Linear)
                   ? (r - m_rmin) / (m_rmax - m_rmin)
                   : qLn(r / m_rmin) / qLn(m_rmax / m_rmin);            // 0 … 1

    return minimum() + qRound(t * (maximum() - minimum()));
}

double Slider::realValue() const          { return fromSlider(value()); }
void   Slider::setRealValue(double r)     { setValue(toSlider(r)); }


bool Slider::event(QEvent *ev) {
    if (ev->type() == QEvent::HoverMove) {
        auto *hev = static_cast<QHoverEvent*>(ev);

        // prepare style-option to ask for the handle rect
        QStyleOptionSlider opt;
        initStyleOption(&opt);
        QRect hr = style()->subControlRect(
            QStyle::CC_Slider, &opt,
            QStyle::SC_SliderHandle, this
            );

        // switch cursor based on whether pointer is in the handle
        QPointF ptF = hev->position();           // floating-point position
        QPoint  pt  = ptF.toPoint();              // convert to integer pixel coords
        if (hr.contains(pt)) {
            setCursor(Qt::PointingHandCursor);
        } else {
            unsetCursor();
        }
    }
    return QSlider::event(ev);
}





