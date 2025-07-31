
#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QFrame>
#include <QHBoxLayout>


class StatusBar : public QFrame
{
    Q_OBJECT
public:
    StatusBar(QWidget* parent = nullptr);
    void setProgress(float percentage);

private:
    QFrame* m_progress_indicator;
    QHBoxLayout* m_main_layout;

};

#endif // STATUSBAR_H
