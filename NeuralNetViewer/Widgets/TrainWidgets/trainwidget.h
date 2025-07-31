
#ifndef TRAINWIDGET_H
#define TRAINWIDGET_H

#include <QFrame>
#include "iconbutton.h"
#include "trainoptionswidget.h"
#include "trainstatuswidget.h"



class TrainWidget : public QFrame
{
    Q_OBJECT
public:
    TrainWidget(QWidget* parent = nullptr);

private:
    TrainOptionsWidget* m_options_widget;
    IconButton* m_train_button;
    IconButton* m_cancel_button;
    TrainStatusWidget* m_status_widget;

signals:
    void batchSizeChanged(int);
    void shuffleDataChanged(bool);
    void useValidationSetChanged(bool);
    void validationSplitChanged(double);


};

#endif // TRAINWIDGET_H
