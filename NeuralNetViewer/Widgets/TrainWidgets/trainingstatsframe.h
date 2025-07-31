
#ifndef TRAININGSTATSFRAME_H
#define TRAININGSTATSFRAME_H

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>



class TrainingStatsFrame : public QFrame
{
    Q_OBJECT
public:
    TrainingStatsFrame(QWidget* parent = nullptr);
    void set_epoch(int epoch);
    void set_accuracy(float accuracy);
    void set_eta(float eta);
    void set_training_loss(float loss);
    void set_validation_loss(float loss);

private:
    QLabel* m_epoch_label;
    QLabel* m_accuracy_label;
    QLabel* m_eta_label;
    QLabel* m_training_loss_label;
    QLabel* m_validation_loss_label;
};

#endif // TRAININGSTATSFRAME_H
