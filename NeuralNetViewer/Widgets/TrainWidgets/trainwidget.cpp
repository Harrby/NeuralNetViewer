
#include "trainwidget.h"
#include <array>
std::array<QString, 3>  ButtonColors = {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"};

TrainWidget::TrainWidget(QWidget* parent)
    : QFrame(parent),
    m_options_widget(new TrainOptionsWidget(this)),
    m_train_button(new IconButton(QString("Train"), ButtonColors, 32, 160, this)),
    m_cancel_button(new IconButton(QString("Cancel"), ButtonColors, 32, 160, this)),
    m_status_widget(new TrainStatusWidget(this))
{
    m_train_button->setFixedHeight(32);
    m_cancel_button->setFixedHeight(32);

    setStyleSheet(".TrainWidget{background-color: #4E4E4E;}");

    QHBoxLayout* main_h_layout = new QHBoxLayout();
    main_h_layout->addStretch(10);
    main_h_layout->addWidget(m_train_button, 12);
    main_h_layout->addStretch(3);
    main_h_layout->addWidget(m_cancel_button, 12);
    main_h_layout->addStretch(10);
    main_h_layout->setContentsMargins(0, 12, 0, 12);


    QVBoxLayout* main_v_layout = new QVBoxLayout(this);
    main_v_layout->addWidget(m_options_widget);
    main_v_layout->addLayout(main_h_layout);
    main_v_layout->addWidget(m_status_widget);

    connect(m_options_widget, &TrainOptionsWidget::batchSizeChanged, this, &TrainWidget::batchSizeChanged);
    connect(m_options_widget, &TrainOptionsWidget::shuffleDataChanged, this, &TrainWidget::shuffleDataChanged);
    connect(m_options_widget, &TrainOptionsWidget::useValidationSetChanged, this, &TrainWidget::useValidationSetChanged);
    connect(m_options_widget, &TrainOptionsWidget::validationSplitChanged, this, &TrainWidget::validationSplitChanged);
}

