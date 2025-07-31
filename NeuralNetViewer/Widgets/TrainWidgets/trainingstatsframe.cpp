
#include "trainingstatsframe.h"

TrainingStatsFrame::TrainingStatsFrame(QWidget* parent)
    : QFrame(parent),
    m_epoch_label(new QLabel(QString("Epoch:  0"))),
    m_accuracy_label(new QLabel(QString("Accuracy:  0%"))),
    m_eta_label(new QLabel(QString("ETA:  0s"))),
    m_training_loss_label(new QLabel(QString("Training Loss:  0"))),
    m_validation_loss_label(new QLabel(QString("Validation Loss:  0")))
{
    setStyleSheet("background-color: #302B2B; color: #ffffff;");

    QHBoxLayout* upper_h_layout = new QHBoxLayout();
    upper_h_layout->addStretch(1);
    upper_h_layout->addWidget(m_epoch_label);
    upper_h_layout->addStretch(1);
    upper_h_layout->addWidget(m_accuracy_label);
    upper_h_layout->addStretch(1);
    upper_h_layout->addWidget(m_eta_label);
    upper_h_layout->addStretch(1);
    upper_h_layout->setContentsMargins(0, 0, 0, 0);
    upper_h_layout->setSpacing(40);

    QHBoxLayout* lower_h_layout = new QHBoxLayout();
    lower_h_layout->addStretch(1);
    lower_h_layout->addWidget(m_training_loss_label);
    lower_h_layout->addStretch(1);
    lower_h_layout->addWidget(m_validation_loss_label);
    lower_h_layout->addStretch(1);
    lower_h_layout->setContentsMargins(0, 0, 0, 0);
    lower_h_layout->setSpacing(30);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addLayout(upper_h_layout);
    main_layout->addLayout(lower_h_layout);
    main_layout->setSpacing(4);
    main_layout->setContentsMargins(6, 6, 6, 6);
}

void TrainingStatsFrame::set_epoch(int epoch){
    m_epoch_label->setText(QString("Epoch:  %1").arg(epoch));
}

void TrainingStatsFrame::set_accuracy(float accuracy){
    accuracy *= 100;
    m_accuracy_label->setText(QString("Accuracy:  %1%").arg(accuracy));
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

