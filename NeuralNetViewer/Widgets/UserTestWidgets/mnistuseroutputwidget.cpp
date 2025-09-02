
#include "mnistuseroutputwidget.h"

MNISTUserOutputWidget::MNISTUserOutputWidget(QWidget* parent)
    : QFrame(parent),
    m_saliencies(Eigen::VectorXf::Zero(784)),
    m_prediction_label(new QLabel(QString("Prediction:"))),
    m_entropy_label(new QLabel(QString("Entropy:"))),
    m_confidence_label(new QLabel(QString("Confidence:"))),
    m_probabilities_log(new LogWidget),
    m_saliency_map(new SaliencyMapArea),
    m_class_label(new QLabel(QString("Class:"))),
    m_saliency_label(new QLabel(QString("Saliency:"))),
    m_pixel_label(new QLabel(QString("Pixel:")))
{
    setStyleSheet(".MNISTUserOutputWidget{background-color: #4E4E4E;} QLabel{color: #ffffff;}");
    setFixedHeight(640);
    setMinimumWidth(500);


    QLabel* title_label = new QLabel(QString("User Output"));
    QHBoxLayout* title_layout = new QHBoxLayout;
    title_layout->addStretch(1);
    title_layout->addWidget(title_label);
    title_layout->addStretch(1);

    QHBoxLayout* upper_stats_layout = new QHBoxLayout;
    upper_stats_layout->addWidget(m_prediction_label);
    upper_stats_layout->addWidget(m_entropy_label);
    upper_stats_layout->addWidget(m_confidence_label);
    upper_stats_layout->setSpacing(10);

    QLabel* probabilities_label = new QLabel(QString("Probabilities"));
    QHBoxLayout* probabilities_title_layout = new QHBoxLayout;
    probabilities_title_layout->addStretch(1);
    probabilities_title_layout->addWidget(probabilities_label);
    probabilities_title_layout->addStretch(1);

    QFrame* output_stats_frame = new QFrame;
    output_stats_frame->setStyleSheet("background-color: #302B2B; border: 0px solid black; border-radius: 4px;");
    QVBoxLayout* output_stats_frame_layout = new QVBoxLayout;
    output_stats_frame_layout->addLayout(title_layout);
    output_stats_frame_layout->addLayout(upper_stats_layout);
    output_stats_frame_layout->addLayout(probabilities_title_layout);
    output_stats_frame_layout->addWidget(m_probabilities_log);
    output_stats_frame->setLayout(output_stats_frame_layout);

    QLabel* saliency_title = new QLabel(QString("Saliency Map"));
    QHBoxLayout* saliency_title_layout = new QHBoxLayout;
    saliency_title_layout->addStretch(1);
    saliency_title_layout->addWidget(saliency_title);
    saliency_title_layout->addStretch(1);
    QFrame* saliency_title_frame = new QFrame;
    saliency_title_frame->setStyleSheet("background-color: #302B2B; border: 0px solid black; border-radius: 4px;");
    saliency_title_frame->setLayout(saliency_title_layout);

    QFrame* saliency_map_frame = new QFrame;
    saliency_map_frame->setObjectName("saliencyMapFrame");
    saliency_map_frame->setStyleSheet("#saliencyMapFrame{background-color: #1FA1E3; border: 0px solid #1FA1E3; border-radius: 4px;}");
    saliency_map_frame->setFixedSize(344, 344);
    QHBoxLayout* saliency_map_layout = new QHBoxLayout(saliency_map_frame);
    saliency_map_layout->setContentsMargins(4, 4, 4, 4);
    saliency_map_layout->setSpacing(0);
    saliency_map_layout->addWidget(m_saliency_map);
    //saliency_map_frame->setLayout(saliency_map_layout);

    QHBoxLayout* saliency_hor_layout = new QHBoxLayout;
    saliency_hor_layout->addStretch(1);
    saliency_hor_layout->addWidget(saliency_map_frame);
    saliency_hor_layout->addStretch(1);


    QFrame* map_stats_frame = new QFrame;
    map_stats_frame->setStyleSheet("background-color: #302B2B; border: 0px solid black; border-radius: 4px;");
    QHBoxLayout* map_stats_layout = new QHBoxLayout;
    map_stats_layout->addWidget(m_class_label);
    map_stats_layout->addWidget(m_saliency_label);
    map_stats_layout->addWidget(m_pixel_label);
    map_stats_frame->setLayout(map_stats_layout);


    QVBoxLayout* main_v_layout = new QVBoxLayout;
    main_v_layout->addWidget(output_stats_frame);
    main_v_layout->addWidget(saliency_title_frame);
    main_v_layout->addLayout(saliency_hor_layout);
    main_v_layout->addWidget(map_stats_frame);

    setLayout(main_v_layout);


    //connections

    connect(m_saliency_map, &SaliencyMapArea::ClickedAt, this, &MNISTUserOutputWidget::onSaliencyMapClicked);





}


void MNISTUserOutputWidget::setSaliencies(Eigen::VectorXf& saliencies){
    m_saliencies = saliencies;
};

void MNISTUserOutputWidget::setAttributes(mnistOutputAttributes& attributes){
    m_prediction_label->setText(QString("Prediction: %1").arg(attributes.predictedClass));
    m_confidence_label->setText(QString("Confidence: %1").arg(attributes.confidence));
    m_entropy_label->setText(QString("Entropy: %1").arg(attributes.entropy));
    setSaliencies(m_saliencies);
    m_saliency_map->setMap(m_saliencies);

    m_probabilities_log->add_probabilites_log_message(attributes.probabilities);


}

void MNISTUserOutputWidget::onSaliencyMapClicked(int x, int y){

}

