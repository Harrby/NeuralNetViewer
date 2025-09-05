
#include "mnistinputwidget.h"

MNISTInputWidget::MNISTInputWidget(QWidget* parent):
    QFrame(parent),
    m_draw_area(new DrawArea),
    m_pen_width_slider(new ValueSliderWidget(QString("Pen Width"), 1, 6, Slider::Linear, 5)),
    m_pen_spread_slider(new ValueSliderWidget(QString("Pen Spread"), 0, 3, Slider::Linear, 3)),
    m_clear_button(new IconButton(":/images/images/cross.png", {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"}, 60, 50)),
    m_predict_button(new IconButton("Predict", {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"}, 1350, 340))
{
    setStyleSheet(".MNISTInputWidget{"
                  "background-color: #4E4E4E;}"
                  );

    setMinimumWidth(360);

    QLabel* title_label = new QLabel(QString("User Input"), this);
    title_label->setStyleSheet("color: #ffffff;");
    QHBoxLayout* title_layout = new QHBoxLayout;
    title_layout->addStretch(1);
    title_layout->addWidget(title_label);
    title_layout->addStretch(1);

    m_pen_width_slider->setValue(static_cast<double>(m_draw_area->get_pen_width()));
    m_pen_spread_slider->setValue(static_cast<double>(m_draw_area->get_feather()));

    m_predict_button->setMaximumHeight(50);

    QVBoxLayout* pen_layout = new QVBoxLayout;
    pen_layout->addWidget(m_pen_width_slider);
    pen_layout->addWidget(m_pen_spread_slider);

    QFrame* title_and_pen_options_frame = new QFrame;
    title_and_pen_options_frame->setStyleSheet("background-color: #302B2B; border: 0px solid black; border-radius: 4px;");
    QVBoxLayout* title_and_pen_options_layout = new QVBoxLayout;
    title_and_pen_options_layout->addLayout(title_layout);
    title_and_pen_options_layout->addLayout(pen_layout);
    title_and_pen_options_frame->setLayout(title_and_pen_options_layout);

    QLabel* canvas_title = new QLabel(QString("Input Canvas"));
    canvas_title->setStyleSheet("color: #ffffff;");
    QHBoxLayout* canvas_title_layout = new QHBoxLayout;
    canvas_title_layout->addStretch(1);
    canvas_title_layout->addWidget(canvas_title);
    canvas_title_layout->addStretch(1);
    QFrame* canvas_title_frame = new QFrame;
    canvas_title_frame->setStyleSheet("background-color: #302B2B; border: 0px solid black; border-radius: 4px;");
    canvas_title_frame->setLayout(canvas_title_layout);

    QFrame* draw_area_frame = new QFrame;
    draw_area_frame->setObjectName("drawAreaFrame");
    draw_area_frame->setStyleSheet("#drawAreaFrame{background-color: #1FA1E3; border: 0px solid #1FA1E3; border-radius: 4px;}");
    draw_area_frame->setFixedSize(344, 344);
    QHBoxLayout* draw_area_layout = new QHBoxLayout;
    draw_area_layout->setContentsMargins(4, 4, 4, 4);
    draw_area_layout->setSpacing(0);
    draw_area_layout->addWidget(m_draw_area);
    draw_area_frame->setLayout(draw_area_layout);

    QHBoxLayout* button_layout = new QHBoxLayout;
    button_layout->addWidget(m_predict_button);
    button_layout->addWidget(m_clear_button);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(title_and_pen_options_frame);
    main_layout->addWidget(canvas_title_frame);
    main_layout->addWidget(draw_area_frame);
    main_layout->addLayout(button_layout);
    main_layout->setContentsMargins(5, 5, 5, 11);

    setLayout(main_layout);



    // INTERNAL CONNECTIONS
    connect(m_pen_width_slider, &ValueSliderWidget::valueChanged, m_draw_area,
            [this](double v){
                m_draw_area->set_pen_width(static_cast<int>(v));
            });

    connect(m_pen_spread_slider, &ValueSliderWidget::valueChanged, m_draw_area,
            [this](double v){
                m_draw_area->set_feather(static_cast<int>(v));
            });

    connect(m_clear_button, &QPushButton::clicked, m_draw_area, &DrawArea::clear);

    connect(m_predict_button, &QPushButton::clicked, this, &MNISTInputWidget::onPredictButtonClicked);




}

void MNISTInputWidget::onPredictButtonClicked(){
    emit PredictionRequest(m_draw_area->export_input());
}

