
#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QFrame>
#include <QTextEdit>


class LogWidget : public QTextEdit
{
    Q_OBJECT
public:
    LogWidget(QWidget* parent = nullptr);
    void add_log_message(QString message);
    void add_training_log_message(int epoch, int total_epochs, float training_loss, float validation_loss, float training_accuracy,
                                  float validation_accuracy, float eta);
    void add_sample_log_message(int sample, int predicted, int actual);
    void add_probabilites_log_message(std::vector<float>& probabilities);
};

#endif // LOGWIDGET_H
