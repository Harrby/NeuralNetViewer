
#include "trainoptionswidget.h"

TrainOptionsWidget::TrainOptionsWidget(QWidget* parent)
    : QFrame(parent),
    m_title(new QLabel(QString("Train"), this)),
    m_dataset_combobox(new ValueComboBoxWidget(QString("Dataset"), {QString("MNIST")}, this)),
    m_batch_size_slider(new ValueSliderWidget(QString("Batch Size"), 1, 256, Slider::Linear, 255, this)),
    m_shuffle_data_checkbox(new ValueCheckboxWidget(QString("Shuffle Data"), this)),
    m_validation_set_checkbox(new ValueCheckboxWidget(QString("Use Validation Set"), this)),
    m_validation_split_slider(new ValueSliderWidget(QString("Validation Split"), 0, 1, Slider::Linear, 100, this))

{
    setStyleSheet(".TrainOptionsWidget{background-color: #302B2B; border: 1px solid #2A2626; border-radius: 4px;}");
    m_title->setStyleSheet("color: #ffffff");
    QFont font = m_title->font();
    font.setPointSize(16);
    m_title->setFont(font);

    QHBoxLayout* title_layout = new QHBoxLayout();
    title_layout->addStretch(1);
    title_layout->addWidget(m_title);
    title_layout->addStretch(1);

    QHBoxLayout* dataset_layout = new QHBoxLayout();
    dataset_layout->addStretch(1);
    dataset_layout->addWidget(m_dataset_combobox, 1);
    dataset_layout->addStretch(1);

    QGridLayout* options_layout = new QGridLayout();
    options_layout->addWidget(m_batch_size_slider, 0, 0);
    options_layout->addWidget(m_shuffle_data_checkbox, 0, 1);
    options_layout->addWidget(m_validation_set_checkbox, 1, 0);
    options_layout->addWidget(m_validation_split_slider, 1, 1);
    options_layout->setHorizontalSpacing(40);
    options_layout->setVerticalSpacing(5);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addLayout(title_layout);
    main_layout->addLayout(dataset_layout);
    main_layout->addLayout(options_layout);

    connect(m_batch_size_slider, &ValueSliderWidget::valueChanged, this,
            [this](double batch_size){
                emit batchSizeChanged(static_cast<int>(batch_size));
            });
    connect(m_shuffle_data_checkbox, &ValueCheckboxWidget::checked, this, &TrainOptionsWidget::shuffleDataChanged);
    connect(m_validation_set_checkbox, &ValueCheckboxWidget::checked, this, &TrainOptionsWidget::useValidationSetChanged);
    connect(m_validation_split_slider, &ValueSliderWidget::valueChanged, this, &TrainOptionsWidget::validationSplitChanged);
}

void TrainOptionsWidget::initialiseParameters(int batch_size, bool shuffle_data, bool use_validation_set, double validation_split){
    m_batch_size_slider->setValue(static_cast<double>(batch_size));
    m_shuffle_data_checkbox->set_state(shuffle_data);
    m_validation_set_checkbox->set_state(use_validation_set);
    m_validation_split_slider->setValue(validation_split);
}

