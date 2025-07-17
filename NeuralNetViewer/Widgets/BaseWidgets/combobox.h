#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include <QEvent>
#include <QHoverEvent>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = nullptr);
    void setFontFamily(const QString& family);
    void addItem(const QString &text, const QVariant &userData);
    void addItems(const QStringList &texts);

protected:                 // ← not private
    bool event(QEvent *e) override;

};

#endif // COMBOBOX_H
