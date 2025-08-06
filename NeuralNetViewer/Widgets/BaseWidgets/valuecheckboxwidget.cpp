
#include "valuecheckboxwidget.h"

ValueCheckboxWidget::ValueCheckboxWidget(QString title_text, QWidget* parent)
    : QFrame(parent),
    m_checkbox(new CheckBox(this)),
    m_title(new QLabel(title_text))
{
    m_title->setStyleSheet("color: #ffffff;");
    setStyleSheet("background-color: #302B2B;");

    QHBoxLayout* main_layout = new QHBoxLayout(this);
    main_layout->addWidget(m_title);
    main_layout->addStretch(4);
    main_layout->addWidget(m_checkbox);
    main_layout->addStretch(1);

    main_layout->setContentsMargins(2, 20, 2, 2);

    connect(m_checkbox, &CheckBox::clicked, this, &ValueCheckboxWidget::checked);

}

bool ValueCheckboxWidget::get_state(){
    return m_checkbox->isChecked();
}

void ValueCheckboxWidget::set_state(bool state){
    m_checkbox->setChecked(state);
}

