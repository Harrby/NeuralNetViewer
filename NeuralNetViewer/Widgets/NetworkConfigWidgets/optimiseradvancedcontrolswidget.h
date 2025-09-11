
#ifndef OPTIMISERADVANCEDCONTROLSWIDGET_H
#define OPTIMISERADVANCEDCONTROLSWIDGET_H

#include <QFrame>
#include "valuesliderwidget.h"
#include <QObject>
#include "QGridLayout"
#include "optimiser_utils.h"
#include <QStackedWidget>

class OptimiserAdvancedControlsWidget : public QFrame
{
    Q_OBJECT
public:
    OptimiserAdvancedControlsWidget(QWidget* parent = nullptr);
    void setOptimiserOptions(OptimiserType optimiser);

    void setSGDOptimiserOptions();
    void setMomentumSGDOptimiserOptions();
    void setRMSPropOptimiserOptions();
    void setAdamOptimiserOptions();
    void clearLayout(QLayout* layout);
    void toggle_visibility();
    void initialise_sliders(float momentum, float beta1, float beta2);



private:
    ValueSliderWidget* m_s_momentum;
    ValueSliderWidget* m_s_beta2_rms;
    ValueSliderWidget* m_s_beta1;
    ValueSliderWidget* m_s_beta2;

    QStackedWidget* m_stacked_widget;
    QVBoxLayout* m_main_layout;

signals:
    void momentumChanged(double);
    void beta1Changed(double);
    void beta2Changed(double);

};

#endif // OPTIMISERADVANCEDCONTROLSWIDGET_H
