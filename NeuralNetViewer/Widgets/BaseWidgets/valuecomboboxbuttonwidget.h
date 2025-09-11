
#ifndef VALUECOMBOBOXBUTTONWIDGET_H
#define VALUECOMBOBOXBUTTONWIDGET_H

#include "iconbutton.h"
#include <QFrame>
#include "combobox.h"
#include "QLabel"
#include <QVBoxLayout>


class ValueComboBoxButtonWidget : public QFrame
{
    Q_OBJECT
public:
    ValueComboBoxButtonWidget(const QString& button_icon, const std::array<QString, 3>& button_colors,
                              const QString& labelText = QString(), const QStringList& options=QStringList(),
                              QWidget* parent=nullptr);
    void setValue(QString new_value);
    void toggle_enable_button(bool enabled);
private:

    ComboBox* m_combobox;
    QLabel* m_label;
    IconButton* m_button;

signals:
    void valueChanged(QString);
    void buttonClicked();

};

#endif // VALUECOMBOBOXBUTTONWIDGET_H
