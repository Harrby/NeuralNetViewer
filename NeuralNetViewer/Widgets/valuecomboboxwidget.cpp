
#include "valuecomboboxwidget.h"
#include <QVBoxLayout>

ValueComboBoxWidget::ValueComboBoxWidget(const QString &labelText, const QStringList &options, QWidget *parent)
    : QFrame(parent),
    m_combobox(new ComboBox(this)),
    m_label(new QLabel(labelText, this))
{
    m_label->setStyleSheet("color: #FFFFFF;");

    setStyleSheet(".ValueComboBoxWidget{background-color: #302B2B;}");

    m_combobox->addItems(options);

    QVBoxLayout *v_layout = new QVBoxLayout(this);
    v_layout->setSpacing(0);
    v_layout->addWidget(m_label);
    v_layout->addWidget(m_combobox);
    v_layout->setContentsMargins(2, 2, 2, 2);

}

void ValueComboBoxWidget::setValue(QString new_value){
    int index = m_combobox->findText(new_value);
    if (index != -1) {
        m_combobox->setCurrentIndex(index);
    }
}

