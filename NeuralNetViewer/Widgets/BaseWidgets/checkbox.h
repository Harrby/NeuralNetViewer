
#ifndef CHECKBOX_H
#define CHECKBOX_H
#include <QCheckBox>



class CheckBox : public QCheckBox
{
    Q_OBJECT
public:
    CheckBox(QWidget *parent=nullptr);
};

#endif // CHECKBOX_H
