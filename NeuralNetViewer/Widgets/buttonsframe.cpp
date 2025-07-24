
#include "buttonsframe.h"

ButtonsFrame::ButtonsFrame(QWidget* parent)
    : QFrame(parent),
    m_add_button(new IconButton(":/images/images/plus.png", {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"}, 60, 60, this)),
    m_remove_button(new IconButton(":/images/images/minus.png", {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"}, 60, 60, this))
{

    setFixedHeight(50);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_add_button, 1);
    layout->addWidget(m_remove_button, 1);
    layout->addStretch(4);
    layout->setSpacing(5);
    layout->setContentsMargins(4, 4, 0, 4);

    connect(m_add_button, &QPushButton::clicked, this, &ButtonsFrame::addButtonClicked);
    connect(m_remove_button, &QPushButton::clicked, this, &ButtonsFrame::removeButtonClicked);
}

