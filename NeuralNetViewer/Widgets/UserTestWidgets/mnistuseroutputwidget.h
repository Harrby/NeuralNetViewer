
#ifndef MNISTUSEROUTPUTWIDGET_H
#define MNISTUSEROUTPUTWIDGET_H

#include <QFrame>
#include<QLabel>
#include <QObject>
#include <QHBoxLayout>
#include "logwidget.h"
#include "saliencymaparea.h"
#include <Eigen/Dense>
#include "predictionresults.h"


class MNISTUserOutputWidget : public QFrame
{
    Q_OBJECT
public:
    MNISTUserOutputWidget(QWidget* parent = nullptr);
    void setSaliencies(Eigen::VectorXf& saliencies);
    void setAttributes(PredictionResults& attributes);


private:
    Eigen::VectorXf m_saliencies;

    QLabel* m_prediction_label;
    QLabel* m_entropy_label;
    QLabel* m_confidence_label;
    LogWidget* m_probabilities_log;
    SaliencyMapArea* m_saliency_map;
    QLabel* m_class_label;
    QLabel* m_saliency_label;
    QLabel* m_pixel_label;

    void onSaliencyMapClicked(int x, int y);

};

#endif // MNISTUSEROUTPUTWIDGET_H
