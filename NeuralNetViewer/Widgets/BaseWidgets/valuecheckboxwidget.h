
#ifndef VALUECHECKBOXWIDGET_H
#define VALUECHECKBOXWIDGET_H

#include <QFrame>
#include <QLabel>
#include "checkbox.h"
#include <QHBoxLayout>



class ValueCheckboxWidget : public QFrame
{
    Q_OBJECT
public:
    ValueCheckboxWidget(QString title_text = "", QWidget* parent = nullptr);
    bool get_state();
    void set_state(bool state);

private:
    CheckBox* m_checkbox;
    QLabel* m_title;
signals:
    void checked(bool);
};

#endif // VALUECHECKBOXWIDGET_H
