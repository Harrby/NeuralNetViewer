
#include "lineedit.h"

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setStyleSheet("background-color: #d9d9d9;"
                  "border-radius: 4px;");
    setMinimumSize(50, 30);
    setAlignment(Qt::AlignCenter);

    QFont f= font();
    f.setPointSize(14);
    setFont(f);
}


void LineEdit::setFontFamily(const QString& family){
    QFont f = font();
    f.setFamily(family);
    setFont(f);
}
