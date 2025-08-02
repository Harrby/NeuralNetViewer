
#include "trainingstatsframe.h"

TrainingStatsFrame::TrainingStatsFrame(QWidget* parent)
    : QFrame(parent),
    m_epoch_label(new QLabel(QString("Epoch:  0"))),
    m_eta_label(new QLabel(QString("ETA:  0s"))),
    m_training_loss_label(new QLabel(QString("Training Loss:  0"))),
    m_validation_loss_label(new QLabel(QString("Validation Loss:  0"))),
    m_training_accuracy_label(new QLabel(QString("Training Accuracy:  0%"))),
    m_validation_accuracy_label(new QLabel(QString("Validation Accuracy:  0%")))
{
    setStyleSheet("background-color: #302B2B; color: #ffffff;");

    QGridLayout* grid_layout = new QGridLayout(this);
    grid_layout->addWidget(m_epoch_label, 0, 0, Qt::AlignLeft);
    grid_layout->addWidget(m_training_loss_label, 1, 0, Qt::AlignLeft);
    grid_layout->addWidget(m_training_accuracy_label, 2, 0, Qt::AlignLeft);
    grid_layout->addWidget(m_eta_label, 0, 1, Qt::AlignLeft);
    grid_layout->addWidget(m_validation_loss_label, 1, 1, Qt::AlignLeft);
    grid_layout->addWidget(m_validation_accuracy_label, 2, 1, Qt::AlignLeft);
    grid_layout->setHorizontalSpacing(12);
    grid_layout->setVerticalSpacing(4);
    grid_layout->setContentsMargins(6, 6, 6, 6);


}

void TrainingStatsFrame::set_epoch_stats(const EpochStats& epoch_stats){
    set_epoch(epoch_stats.epoch);
    set_training_accuracy(epoch_stats.training_accuracy);
    set_validation_accuracy(epoch_stats.validation_accuracy);
    set_training_loss(epoch_stats.training_loss);
    set_validation_loss(epoch_stats.validation_loss);
    set_eta(epoch_stats.eta);
}


void TrainingStatsFrame::set_epoch(int epoch){
    m_epoch_label->setText(QString("Epoch:  %1").arg(epoch));
}

void TrainingStatsFrame::set_training_accuracy(float accuracy){
    accuracy *= 100;
    m_training_accuracy_label->setText(QString("Training Accuracy:  %1%").arg(accuracy));
}

void TrainingStatsFrame::set_validation_accuracy(float accuracy){
    accuracy *= 100;
    m_validation_accuracy_label->setText(QString("Validation Accuracy:  %1%").arg(accuracy));
}

void TrainingStatsFrame::set_eta(float eta)
{
    int totalSeconds = static_cast<int>(eta);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    QString text;
    if (minutes > 0)
        text = QString("ETA: %1m %2s").arg(minutes).arg(seconds);
    else
        text = QString("ETA: %1s").arg(seconds);

    m_eta_label->setText(text);
}

void TrainingStatsFrame::set_training_loss(float loss){
    m_training_loss_label->setText(QString("Training Loss:  %1").arg(loss));

}
void TrainingStatsFrame::set_validation_loss(float loss){
    m_validation_loss_label->setText(QString("Validation Loss:  %1").arg(loss));

}

