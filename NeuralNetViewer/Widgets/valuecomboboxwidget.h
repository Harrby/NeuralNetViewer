
#ifndef VALUECOMBOBOXWIDGET_H
#define VALUECOMBOBOXWIDGET_H
#include <QFrame>
#include <QLabel>
#include "combobox.h"



class ValueComboBoxWidget : public QFrame
{
    Q_OBJECT
public:
    ValueComboBoxWidget(const QString &labelText = QString(),const QStringList &options=QStringList(),  QWidget *parent=nullptr);
    void setValue(QString new_value);

private:
    ComboBox* m_combobox;
    QLabel* m_label;

};

#endif // VALUECOMBOBOXWIDGET_H
