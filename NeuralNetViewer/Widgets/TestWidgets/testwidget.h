
#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QFrame>

#include <QObject>

#include "valuecomboboxwidget.h"
#include "iconbutton.h"
#include "statusbar.h"
#include "teststatusstats.h"



class TestWidget : public QFrame
{
    Q_OBJECT
public:
    TestWidget(QWidget* parent = nullptr);

    void setStatusData(TestStatusStats& test_stats);


private:
    std::array<QString, 3>  ButtonColors = {"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"};


    ValueComboBoxWidget* m_dataset_selector;
    QLabel* m_samples_label;
    QLabel* m_features_label;
    QLabel* m_classes_label;
    IconButton* m_test_button;
    IconButton* m_cancel_button;
    StatusBar* m_status_bar;
    QLabel* m_sample_label;
    QLabel* m_eta_label;

signals:
    void testButtonClicked();
    void cancelButtonClicked();


};

#endif // TESTWIDGET_H
