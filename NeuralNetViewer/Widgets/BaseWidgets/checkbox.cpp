
#include "checkbox.h"

CheckBox::CheckBox(QWidget *parent)
    : QCheckBox(parent)
{
    setCursor(Qt::PointingHandCursor);
    setFixedSize(32, 32);

    setStyleSheet(R"(
        /* ---------- label text ---------- */
        QCheckBox {
            spacing: 8px;           /* gap between box and text   */
            color: #d9d9d9;         /* label colour                */
        }

        /* ---------- indicator size (the square) ---------- */
        QCheckBox::indicator {
            width: 32px;
            height: 32px;
        }

        /* ---------- unchecked look ---------- */
        QCheckBox::indicator:unchecked {
            background-color: #d9d9d9;
            border: 0px solid #d9d9d9;
            border-radius: 4px;     /* rounded corners             */
        }

        /* ---------- checked look ---------- */
        QCheckBox::indicator:checked {
            image: url(:/images/images/checkbox_tick); /* your tick symbol  */
            background: #d9d9d9;                /* green fill        */
            border: 0px solid #4caf50;
            border-radius: 4px;
        }

        /* ---------- hover effect (optional) ---------- */
        QCheckBox::indicator:hover {
            border-color: #aaaaaa;
        }
    )");

}

