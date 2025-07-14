
#include "valuesliderwidget.h"
#include "slider.h"
#include <QHBoxLayout>

ValueSliderWidget::ValueSliderWidget(const QString &labelText,
                                     double min_value,
                                     double max_value,
                                     Slider::Scale scale,
                                     int steps,
                                     QWidget *parent)
    : QFrame(parent),
    m_min(min_value),
    m_max(max_value),
    m_slider (new Slider(Qt::Horizontal, min_value, max_value, scale, steps,  this)),
    m_lineEdit (new LineEdit(this)),
    m_label (new QLabel(labelText, this))
{
    QDoubleValidator *validator = new QDoubleValidator(m_min, m_max, 6, this);
    validator->setNotation(QDoubleValidator::ScientificNotation);
    m_lineEdit->setValidator(validator);

    m_label->setStyleSheet("color: #FFFFFF;");
    setStyleSheet("background-color: #302B2B;");
    QHBoxLayout* lay_h = new QHBoxLayout;
    lay_h->setSpacing(10);
    lay_h->addWidget(m_slider);
    lay_h->addWidget(m_lineEdit);

    lay_h->setStretch(0, 3);
    lay_h->setStretch(1, 1);
    lay_h->setContentsMargins(0, 0, 0, 0);

    //lay_h->setContentsMargins(20, 30, 20, 30);
    QVBoxLayout* lay_v = new QVBoxLayout(this);
    lay_v->setSpacing(0);
    lay_v->addWidget(m_label);
    lay_v->addLayout(lay_h);
    lay_v->setContentsMargins(2, 2, 2, 2);

    connect(m_slider,    &Slider::realValueChanged,
            m_lineEdit,  [this](double v){
                m_lineEdit->setText(QString::number(v));
            });
    m_lineEdit->setText(QString::number(m_slider->realValue()));

    connect(m_lineEdit, &QLineEdit::editingFinished,
            this,               // context object
            [this] {
                m_slider->setRealValue(m_lineEdit->text().toDouble());
            });


}



