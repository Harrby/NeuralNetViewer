
#include "testwidget.h"


TestWidget::TestWidget(QWidget* parent)
    : QFrame(parent),
    m_dataset_selector(new ValueComboBoxWidget(QString("Dataset"), {"MNIST"})),
    m_samples_label(new QLabel(QString("Samples: "))),
    m_features_label(new QLabel(QString("Features: "))),
    m_classes_label(new QLabel(QString("Classes: "))),
    m_test_button(new IconButton(QString("Test"), ButtonColors, 50, 200)),
    m_cancel_button(new IconButton(QString("Cancel"), ButtonColors, 50, 200)),
    m_status_bar(new StatusBar),
    m_sample_label(new QLabel(QString("Sample: "))),
    m_eta_label(new QLabel(QString("Eta: ")))

{
    setStyleSheet("TestWidget{background-color: #4E4E4E;} QLabel{color: #ffffff;}");
    QString qframe_style_sheet = QString("QFrame{background-color: #302B2B; border: 0px solid black; border-radius: 4px;}");


    QLabel* title_label = new QLabel(QString("Test Input"));
    QHBoxLayout* title_layout = new QHBoxLayout;
    title_layout->addStretch(1);
    title_layout->addWidget(title_label);
    title_layout->addStretch(1);

    QHBoxLayout* dataset_layout = new QHBoxLayout;
    dataset_layout->addStretch(1);
    m_dataset_selector->setMinimumWidth(150);
    dataset_layout->addWidget(m_dataset_selector, 2);
    dataset_layout->addStretch(1);

    QGridLayout* dataset_features_layout = new QGridLayout;
    dataset_features_layout->setContentsMargins(12, 6, 12, 6);
    dataset_features_layout->setHorizontalSpacing(8);
    dataset_features_layout->addWidget(m_samples_label, 0, 0);
    dataset_features_layout->addWidget(m_features_label, 0, 1);
    dataset_features_layout->addWidget(m_classes_label, 1, 0);

    QFrame* data_set_frame = new QFrame;
    data_set_frame->setObjectName("DatasetFrame");
    data_set_frame->setStyleSheet(QString("#DatasetFrame{background-color: #302B2B; border: 0px solid black; border-radius: 4px;}"));
    QVBoxLayout* data_set_frame_layout = new QVBoxLayout;
    data_set_frame_layout->setSpacing(10);
    data_set_frame_layout->addLayout(title_layout);
    data_set_frame_layout->addLayout(dataset_layout);
    data_set_frame_layout->addLayout(dataset_features_layout);
    data_set_frame->setLayout(data_set_frame_layout);


    QHBoxLayout* buttons_hor_layout = new QHBoxLayout;
    m_test_button->setMaximumHeight(50);
    m_cancel_button->setMinimumHeight(50);
    buttons_hor_layout->addWidget(m_test_button);
    buttons_hor_layout->addWidget(m_cancel_button);


    QLabel* status_title_label = new QLabel(QString("Status"));
    QHBoxLayout* status_title_layout = new QHBoxLayout;
    status_title_layout->addStretch(1);
    status_title_layout->addWidget(status_title_label);
    status_title_layout->addStretch(1);

    QHBoxLayout* status_stats_layout = new QHBoxLayout;
    status_stats_layout->setContentsMargins(12, 6, 12, 6);
    status_stats_layout->addWidget(m_sample_label);
    status_stats_layout->addWidget(m_eta_label);

    QFrame* status_frame = new QFrame;
    status_frame->setStyleSheet(qframe_style_sheet);
    QVBoxLayout* status_frame_layout = new QVBoxLayout;
    status_frame_layout->setSpacing(10);
    status_frame_layout->addLayout(status_title_layout);
    m_status_bar->setFixedHeight(25);
    status_frame_layout->addWidget(m_status_bar);
    status_frame_layout->addLayout(status_stats_layout);
    status_frame_layout->addSpacing(20);
    status_frame->setLayout(status_frame_layout);


    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(data_set_frame);
    main_layout->addLayout(buttons_hor_layout);
    main_layout->addWidget(status_frame);
    main_layout->setContentsMargins(5, 11, 5, 5);

    onComboBoxValueChanged("MNIST");

    setLayout(main_layout);

    //connections

    connect(m_test_button, &QPushButton::clicked, this, &TestWidget::testButtonClicked);
    connect(m_cancel_button, &QPushButton::clicked, this, &TestWidget::cancelButtonClicked);
    connect(m_dataset_selector, &ValueComboBoxWidget::valueChanged, this, &TestWidget::onComboBoxValueChanged);

}

void TestWidget::setStatusData(TestStatusStats& test_stats){
    m_sample_label->setText(QString("Sample: %1").arg(test_stats.current_sample));
    m_eta_label->setText(QString("ETA: %1").arg(test_stats.eta));
    m_status_bar->setProgress(static_cast<float>(test_stats.current_sample) / test_stats.total_samples);
    // force updates - so user can see ETA and sample number live.
    m_sample_label->repaint();
    m_eta_label->repaint();
    m_status_bar->repaint();
}

void TestWidget::onComboBoxValueChanged(QString value){
    int samples;
    int features;
    int classes;


    if (value == "MNIST"){
        samples = 10000;
        features = 784;
        classes = 10;
    } else{
        samples = 0;
        features = 0;
        classes = 0;
    }

    m_samples_label->setText(QString("Samples: %1").arg(samples));
    m_features_label->setText(QString("features: %1").arg(features));
    m_classes_label->setText(QString("Classes: %1").arg(classes));


}

