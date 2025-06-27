
#ifndef LINEEDIT_H
#define LINEEDIT_H
#include <QLineEdit>
#include <QFont>




class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget *parent=nullptr);
    void setFontFamily(const QString& family);


};

#endif // LINEEDIT_H
