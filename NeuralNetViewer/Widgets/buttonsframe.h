
#ifndef BUTTONSFRAME_H
#define BUTTONSFRAME_H

#include <QFrame>
#include "iconbutton.h"
#include <QHBoxLayout>


class ButtonsFrame : public QFrame
{
    Q_OBJECT
public:
    ButtonsFrame(QWidget* parent=nullptr);

private:
    IconButton* m_add_button;
    IconButton* m_remove_button;

signals:
    void addButtonClicked();
    void removeButtonClicked();
};

#endif // BUTTONSFRAME_H
