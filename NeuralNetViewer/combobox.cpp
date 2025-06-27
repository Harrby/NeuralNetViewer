#include "combobox.h"

ComboBox::ComboBox(QWidget *parent)
: QComboBox(parent)
{
    setFixedHeight(30);
    setStyleSheet(R"(
    QComboBox {
        background-color: #d9d9d9;
        border: 0px solid #888;
        border-radius: 4px;
        padding-left: 6px;       /* room for icon or text */
    }
    QComboBox::drop-down {
        width: 24px;
        background-color: #d9d9d9;
        border: 0px solid #888;
        border-radius: 4px;             /* arrow button */
    }
    QComboBox::down-arrow {
        image: url(:/images/images/dropdownarrow.png);
        width:24px;
        height: 20px;
    }
)");



}

bool ComboBox::event(QEvent *e)
{
    if (e->type() == QEvent::HoverMove) {
        auto *he = static_cast<QHoverEvent*>(e);

        QStyleOptionComboBox opt;
        initStyleOption(&opt);

        auto sc = style()->hitTestComplexControl(QStyle::CC_ComboBox,
                                                 &opt, he->position().toPoint(), this);
        if (sc == QStyle::SC_ComboBoxArrow)
            setCursor(Qt::PointingHandCursor);
        else
            unsetCursor();
    }
    return QComboBox::event(e);
}

void ComboBox::setFontFamily(const QString& family){
    QFont f = font();
    f.setFamily(family);
    setFont(f);
}

void ComboBox::addItem(const QString &text, const QVariant &userData)
{
    QComboBox::addItem(text, userData);
    setItemData(count() - 1, Qt::AlignCenter, Qt::TextAlignmentRole);
}

void ComboBox::addItems(const QStringList &texts)
{
    int start = count();
    QComboBox::addItems(texts);
    for (int i = start; i < count(); ++i)
        setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
}
