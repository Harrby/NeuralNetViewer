
#ifndef TRAINOPTIONSWIDGET_H
#define TRAINOPTIONSWIDGET_H

#include <QFrame>
#include "valuecomboboxwidget.h"
#include "valuesliderwidget.h"
#include "valuecheckboxwidget.h"


class TrainOptionsWidget : public QFrame
{
    Q_OBJECT
public:
    TrainOptionsWidget(QWidget* parent = nullptr);
    void initialiseParameters(int batch_size, bool shuffle_data, bool use_validation_set, double validation_split);


private:
    QLabel* m_title;
    ValueComboBoxWidget* m_dataset_combobox;
    ValueSliderWidget* m_batch_size_slider;
    ValueCheckboxWidget* m_shuffle_data_checkbox;
    ValueCheckboxWidget* m_validation_set_checkbox;
    ValueSliderWidget* m_validation_split_slider;

signals:
    void batchSizeChanged(int);
    void shuffleDataChanged(bool);
    void useValidationSetChanged(bool);
    void validationSplitChanged(double);


};

#endif // TRAINOPTIONSWIDGET_H
