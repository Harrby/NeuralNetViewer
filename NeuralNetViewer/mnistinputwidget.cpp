
#include "mnistinputwidget.h"

MNISTInputWidget::MNISTInputWidget(QWidget* parent):
    QFrame(parent),
    m_draw_area(new DrawArea(this)),
    m_draw_area_frame(new QFrame(this)),
    m_title_frame(new QFrame(this)),
    m_pen_options_frame(new QFrame(this)),
    m_clear_button(new IconButton(":/images/images/cross.png", {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"}, 60, 50,this)),
    m_predict_button(new IconButton("Predict", {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"}, 1350, 340, this))
{
    setStyleSheet(".MNISTInputWidget{"
                  "background-color: #696C6D;}");

    // Title Frame
    QLabel* title_label = new QLabel(QString("MNIST Input"), this);
    title_label->setAlignment(Qt::AlignCenter);
    QHBoxLayout* title_layout = new QHBoxLayout(m_title_frame);
    title_layout->addWidget(title_label, Qt::AlignCenter);
    m_title_frame->setObjectName("titleFrame");
    m_title_frame->setStyleSheet("#titleFrame{background-color: #302B2B; border: 1px solid #2A2626; border-radius: 4px;}");
    title_label->setStyleSheet("color: #FFFFFF;");

    // Pen Options Frame
    m_pen_options_frame->setObjectName("penOptionsFrame");
    m_pen_options_frame->setStyleSheet("#penOptionsFrame{background-color: #302B2B; border: 1px solid #2A2626; border-radius: 4px;}");
    ValueSliderWidget* pen_width_slider = new ValueSliderWidget(QString("Pen Width"), 1, 6, Slider::Linear, 5, this);
    pen_width_slider->setValue(static_cast<double>(m_draw_area->get_pen_width()));
    ValueSliderWidget* pen_spread_slider = new ValueSliderWidget(QString("Pen Spread"), 0, 3, Slider::Linear, 3, this);
    pen_spread_slider->setValue(static_cast<double>(m_draw_area->get_feather()));
    QVBoxLayout* pen_v_layout = new QVBoxLayout(m_pen_options_frame);
    pen_v_layout->addWidget(pen_width_slider);
    pen_v_layout->addWidget(pen_spread_slider);
    pen_v_layout->setContentsMargins(24, 6, 60, 6);

    m_predict_button->setFixedHeight(50);

    m_draw_area_frame->setObjectName("drawAreaFrame");
    m_draw_area_frame->setStyleSheet("#drawAreaFrame{background-color: #1FA1E3; border: 0px solid #1FA1E3; border-radius: 4px;}");
    m_draw_area_frame->setFixedSize(344, 344);
    QHBoxLayout* draw_area_layout = new QHBoxLayout(m_draw_area_frame);
    draw_area_layout->setContentsMargins(4, 4, 4, 4);
    draw_area_layout->setSpacing(0);
    draw_area_layout->addWidget(m_draw_area);


    QVBoxLayout* clear_button_v_layout = new QVBoxLayout();
    clear_button_v_layout->addStretch(1);
    clear_button_v_layout->addWidget(m_clear_button);
    clear_button_v_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* canvas_options_h_layout = new QHBoxLayout();
    canvas_options_h_layout->addWidget(m_pen_options_frame);
    m_clear_button->setFixedSize(60, 50);
    canvas_options_h_layout->addLayout(clear_button_v_layout);
    canvas_options_h_layout->setSpacing(14);
    canvas_options_h_layout->setContentsMargins(0, 0, 6, 0);

    QHBoxLayout* draw_area_outer_layout = new QHBoxLayout();
    draw_area_outer_layout->addWidget(m_draw_area_frame, Qt::AlignCenter);
    draw_area_outer_layout->setContentsMargins(12, 2, 12, 6);


    QHBoxLayout* predict_button_layout = new QHBoxLayout();
    predict_button_layout->addStretch(1);
    predict_button_layout->addWidget(m_predict_button, 2,Qt::AlignCenter);
    predict_button_layout->addStretch(1);




    QVBoxLayout* main_v_layout = new QVBoxLayout(this);
    main_v_layout->addWidget(m_title_frame, Qt::AlignCenter);
    main_v_layout->addLayout(canvas_options_h_layout, Qt::AlignCenter);
    main_v_layout->addLayout(draw_area_outer_layout);
    main_v_layout->addLayout(predict_button_layout, Qt::AlignCenter);
    main_v_layout->setSpacing(2);
    main_v_layout->setContentsMargins(2, 0, 2, 20);


    // INTERNAL CONNECTIONS
    connect(pen_width_slider, &ValueSliderWidget::valueChanged, m_draw_area,
            [this](double v){
                m_draw_area->set_pen_width(static_cast<int>(v));
            });

    connect(pen_spread_slider, &ValueSliderWidget::valueChanged, m_draw_area,
            [this](double v){
                m_draw_area->set_feather(static_cast<int>(v));
            });

    connect(m_clear_button, &QPushButton::clicked, m_draw_area, &DrawArea::clear);




}

