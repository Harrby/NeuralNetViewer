
#ifndef LAYEROPTIONS_H
#define LAYEROPTIONS_H
#include <QFrame>
#include "checkbox.h"
#include "valuecomboboxwidget.h"
#include "valuesliderwidget.h"
#include <QGridLayout>
#include "neuralnetlayerdata.h"
#include "initialisation_utils.h"


class LayerOptions : public QFrame
{
    Q_OBJECT
public:
    LayerOptions(const NeuralNetLayerData& parameters, int id=1, QWidget *parent=nullptr);
    virtual ~LayerOptions() = default;

    virtual void setAllParameters(const NeuralNetLayerData& parameters);

    void setActive(bool active);
    void setActivationFunction(ActivationFunctionType activation_function);
    void setWeightInit(WeightInitialisationType weight_init);
    void setL1Regularisation(double l1_regularisation);
    void setL2Regularisation(double l2_regularisation);
    virtual void setAsFinalLayer(bool) {}

protected:
    int m_id;
    QLabel* m_title;
    CheckBox* m_checkbox;
    ValueComboBoxWidget* m_cb_activation_function;
    ValueComboBoxWidget* m_cb_weight_initialisation;
    ValueSliderWidget* m_s_l1_regularisation;
    ValueSliderWidget* m_s_l2_regularisation;

signals:
    void activeChanged(int, bool);
    void neuronsChanged(int, int);
    void dropoutRateChanged(int, double);
    void activationFunctionChanged(int, ActivationFunctionType);
    void weightInitChanged(int, WeightInitialisationType);
    void l1RegularisationChanged(int, double);
    void l2RegularisationChanged(int, double);



};

#endif // LAYEROPTIONS_H
