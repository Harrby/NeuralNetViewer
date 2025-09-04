
#ifndef TRAINWIDGET_H
#define TRAINWIDGET_H

#include <QFrame>
#include "iconbutton.h"
#include "trainoptionswidget.h"
#include "trainstatuswidget.h"
#include "epochstats.h"



class TrainWidget : public QFrame
{
    Q_OBJECT
public:
    TrainWidget(QWidget* parent = nullptr);
    void setEpochTrainingData(const EpochStats& epoch_stats);
    void initialiseUIParameters(int batch_size, bool shuffle_data, bool use_validation_set, double valdiation_split);

private:
    TrainOptionsWidget* m_options_widget;
    IconButton* m_train_button;
    IconButton* m_cancel_button;
    TrainStatusWidget* m_status_widget;

    void onTrainButtonClicked();

signals:
    void batchSizeChanged(int);
    void shuffleDataChanged(bool);
    void useValidationSetChanged(bool);
    void validationSplitChanged(double);

    void trainButtonClicked();
    void cancelButtonClicked();


};

#endif // TRAINWIDGET_H
