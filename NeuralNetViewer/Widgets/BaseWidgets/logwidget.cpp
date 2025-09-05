
#include "logwidget.h"


LogWidget::LogWidget(QWidget* parent)
    :QTextEdit(parent)
{
    setStyleSheet("background-color: #D9D9D9; color: black; border 0px solid black; border-radius: 4px;");
    setReadOnly(true);
}

void LogWidget::add_log_message(QString message){
    append(message);
}



void LogWidget::add_training_log_message(int epoch, int total_epochs, float training_loss, float validation_loss, float training_accuracy,
                                         float validation_accuracy, float eta){
    training_accuracy *= 100;
    validation_accuracy *= 100;

    int totalSeconds = static_cast<int>(eta);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    QString eta_text;
    if (minutes > 0)
        eta_text = QString("ETA: %1m %2s").arg(minutes).arg(seconds);
    else
        eta_text = QString("ETA: %1s").arg(seconds);


    QString message = QString("Epoch: %1/%2 - training loss: %3 - validation loss: %4 - training acc: %5% - validation acc: %6% - ETA %7")
                          .arg(epoch)
                          .arg(total_epochs)
                          .arg(training_loss, 0, 'f', 2)
                          .arg(validation_loss, 0, 'f', 2)
                          .arg(training_accuracy, 0, 'f', 2)
                          .arg(validation_accuracy, 0, 'f', 2)
                          .arg(eta_text);
    append(message);
}

void LogWidget::add_sample_log_message(const QVector<SampleLogMessageStats>& log_stats){
    qDebug() << "added sample log message";
    QString message = "";
    QString correct_text;
    for (int i=0; i < log_stats.size(); i++){
        if (log_stats[i].predicted == log_stats[i].actual){
            correct_text = QString("Yes");
        } else{
            correct_text = QString("No");
        }
        message.append(QString("sample: #%1 - predicted: %2 - actual: %3 - correct: %4.\n")
                              .arg(log_stats[i].sample)
                              .arg(log_stats[i].predicted)
                              .arg(log_stats[i].actual)
                           .arg(correct_text));



    }
    append(message);
}

void LogWidget::add_probabilites_log_message(Eigen::VectorXf& probabilities){
    for(int i=0; i < probabilities.size(); i++){
        QString message = QString("Class: %1 - %2").arg(i).arg(probabilities[i]);
        append(message);
    }
}


