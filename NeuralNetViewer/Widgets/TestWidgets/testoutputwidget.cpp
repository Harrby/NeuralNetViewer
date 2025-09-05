
#include "testoutputwidget.h"

TestOutputWidget::TestOutputWidget(QWidget* parent)
    : QFrame(parent),
    m_accuracy_label(new QLabel(QString("Accuracy:"))),
    m_loss_label(new QLabel(QString("Loss:"))),
    m_log_widget(new LogWidget)
{
    m_log_widget->setMinimumHeight(200);

    setStyleSheet("TestOutputWidget{background-color: #4E4E4E;} QLabel{color: #ffffff;}");

    QLabel* title_label = new QLabel(QString("Test Output"));
    QHBoxLayout* title_layout = new QHBoxLayout;
    title_layout->addStretch(1);
    title_layout->addWidget(title_label);
    title_layout->addStretch(1);

    QHBoxLayout* stats_layout = new QHBoxLayout;
    stats_layout->addWidget(m_accuracy_label);
    stats_layout->addWidget(m_loss_label);

    QVBoxLayout* frame_layout = new QVBoxLayout;
    frame_layout->addLayout(title_layout);
    frame_layout->addLayout(stats_layout);
    frame_layout->addWidget(m_log_widget);


    QFrame* inner_frame = new QFrame;
    inner_frame->setObjectName("InnerFrame");
    inner_frame->setStyleSheet("#InnerFrame {background-color: #302B2B; border: 0px solid black; border-radius: 4px;}");
    inner_frame->setLayout(frame_layout);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(inner_frame);
    main_layout->setContentsMargins(5, 11, 5, 5);

    setLayout(main_layout);

}

void TestOutputWidget::setOutputStats(TestOutputStats& stats){
    m_accuracy_label->setText(QString("Accuracy: %1").arg(stats.accuracy));
    m_loss_label->setText(QString("Loss: %1").arg(stats.loss));
    qDebug() << "log stats size is" << stats.log_stats.size();
    for (int i=0; i < stats.log_stats.size(); i++){
        m_log_widget->add_sample_log_message(stats.log_stats[i]);
    }

};

void TestOutputWidget::clear(){
    m_accuracy_label->setText(QString("Accuracy:"));
    m_loss_label->setText(QString("Loss:"));
    m_log_widget->clear();
};


