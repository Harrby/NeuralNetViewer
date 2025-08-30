
#include "trainstatuswidget.h"

TrainStatusWidget::TrainStatusWidget(QWidget* parent)
    :QFrame(parent),
    m_title_label(new QLabel(QString("Status"), this)),
    m_status_bar(new StatusBar(this)),
    m_stats_frame(new TrainingStatsFrame(this)),
    m_graph_widget(new GraphWidget(this)),
    m_log_title_label(new QLabel(QString("Log"),this)),
    m_log_widget(new LogWidget(this))
{
    setStyleSheet(".TrainStatusWidget{background-color: #302B2B; border 0px solid black; border-radius: 4px;}");
    m_title_label->setStyleSheet("color: #ffffff;");
    m_log_title_label->setStyleSheet("color: #ffffff;");


    m_title_label->setFixedHeight(30);
    m_status_bar->setFixedHeight(25);
    m_stats_frame->setFixedHeight(90);
    m_graph_widget->setFixedHeight(300);
    m_log_title_label->setFixedHeight(30);
    m_log_widget->setMinimumHeight(150);


    QHBoxLayout* title_h_layout = new QHBoxLayout();
    title_h_layout->addStretch(1);
    title_h_layout->addWidget(m_title_label);
    title_h_layout->addStretch(1);

    QHBoxLayout* log_title_h_layout = new QHBoxLayout();
    log_title_h_layout->addStretch(1);
    log_title_h_layout->addWidget(m_log_title_label);
    log_title_h_layout->addStretch(1);


    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addLayout(title_h_layout);
    main_layout->addWidget(m_status_bar);
    main_layout->addWidget(m_stats_frame);
    main_layout->addWidget(m_graph_widget);
    main_layout->addLayout(log_title_h_layout);
    main_layout->addWidget(m_log_widget);
    main_layout->setSpacing(2);
    main_layout->setContentsMargins(12, 0, 12, 30);
}

void TrainStatusWidget::setEpochTrainingData(const EpochStats& epoch_stats){
    m_status_bar->setProgress(static_cast<float>(epoch_stats.epoch) / static_cast<float>(epoch_stats.total_epochs));
    m_stats_frame->set_epoch_stats(epoch_stats);
    m_graph_widget->update_training_loss_data(epoch_stats.epoch, epoch_stats.training_loss);
    m_graph_widget->update_validation_loss_data(epoch_stats.epoch, epoch_stats.training_loss);
    m_graph_widget->reset_view();
    m_log_widget->add_training_log_message(epoch_stats.epoch, epoch_stats.total_epochs, epoch_stats.training_loss,
                                           epoch_stats.validation_loss, epoch_stats.training_accuracy,
                                           epoch_stats.validation_accuracy, epoch_stats.eta);

}

