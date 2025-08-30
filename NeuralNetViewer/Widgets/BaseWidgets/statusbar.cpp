
#include "statusbar.h"

StatusBar::StatusBar(QWidget* parent)
    :QFrame(parent),
    m_progress_indicator(new QFrame(this)),
    m_main_layout(new QHBoxLayout(this))
{
    setStyleSheet(".StatusBar{background-color: #f9f9f9; border: 0px solid black; border-radius: 4px;}");

    m_progress_indicator->setStyleSheet("background-color: #1FA1E3; border-top-left-radius: 4px; border-bottom-right-radius: 4px; ");

    m_main_layout->addWidget(m_progress_indicator);
    m_main_layout->setContentsMargins(0, 0, 0, 0);
    m_main_layout->addStretch(1);
}

void StatusBar::setProgress(float percentage){

    m_progress_indicator->setFixedWidth(static_cast<int>(width() * percentage));
}

