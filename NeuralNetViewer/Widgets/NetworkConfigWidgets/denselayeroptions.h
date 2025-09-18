
#ifndef DENSELAYEROPTIONS_H
#define DENSELAYEROPTIONS_H

#include "layeroptions.h"



class DenseLayerOptions : public LayerOptions
{
    Q_OBJECT
public:
    DenseLayerOptions(const NeuralNetLayerData& parameters, int id=1, QWidget *parent=nullptr);

    void setAllParameters(const NeuralNetLayerData& parameters) override;

    void setNeurons(int neurons);
    void setDropoutRate(double dropout_rate);

    void setAsFinalLayer(bool final) override;

private:
    ValueSliderWidget* m_s_neurons;
    ValueSliderWidget* m_s_dropout_rate;
    void initFromParameters(const NeuralNetLayerData& parameters);


};

#endif // DENSELAYEROPTIONS_H
