
#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>
#include <QPainter>
#include <QStyle>
#include <QEvent>
#include <QHoverEvent>
#include <QStyleOptionSlider>




class Slider : public QSlider
{
    Q_OBJECT

public:
    enum Scale { Linear, Logarithmic };

    Slider(Qt::Orientation orientation,
           double      minReal= 0,
           double      maxReal= 100,
           Scale       scale  = Linear,
           int         steps  = 100,
           QWidget*    parent = nullptr);

    double realValue() const;          // 1 → 1000 etc.
    void   setRealValue(double v);     // programmatic change

signals:
    void   realValueChanged(double);   // emit after every move

private:
    double m_rmin, m_rmax;
    Scale  m_scale;

    // helpers
    double  fromSlider(int i)  const;     // int  → real
    int     toSlider(double r) const;     // real → int

protected:
    /**
 * @brief Handle hover-move events to change the cursor over the handle.
 * @details
 *      Intercepts QEvent::HoverMove, determines if the mouse is over the slider's
 *      handle sub-control, and sets cursor to QT::PoitingHandCursor. All other events
 *      are forwarded to QSlider::event().
 * @param ev: the incoming event to process.
 * @return true if event was handled here, otherwise value returned by QSlider::event(ev).
 * @override
 */
    bool event(QEvent *ev) override;
};

#endif // SLIDER_H
