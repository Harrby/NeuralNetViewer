
#include "valuecomboboxbuttonwidget.h"

ValueComboBoxButtonWidget::ValueComboBoxButtonWidget(const QString& button_icon, const std::array<QString, 3>& button_colors,
                                                     const QString& labelText, const QStringList& options,
                                                     QWidget* parent)
    : QFrame(parent),
    m_combobox(new ComboBox),
    m_label(new QLabel(labelText)),
    m_button(new IconButton(button_icon, button_colors, 50, 50, this))
{
    m_label->setStyleSheet("color: #FFFFFF;");
    m_button->setAttribute(Qt::WA_StyledBackground);

    setStyleSheet(".ValueComboBoxButtonWidget{background-color: #302B2B;}");

    m_combobox->addItems(options);


    QHBoxLayout* h_layout = new QHBoxLayout;
    h_layout->setSpacing(6);
    h_layout->addWidget(m_combobox);
    h_layout->addWidget(m_button);
    h_layout->setContentsMargins(2, 2, 2, 2);

    QVBoxLayout* v_layout = new QVBoxLayout;
    v_layout->setSpacing(0);
    v_layout->addWidget(m_label);
    v_layout->addLayout(h_layout);
    v_layout->setContentsMargins(2, 2, 2, 2);
    setLayout(v_layout);

    connect(m_combobox, &ComboBox::currentTextChanged, this, &ValueComboBoxButtonWidget::valueChanged);
    connect(m_button, &IconButton::clicked, this, &ValueComboBoxButtonWidget::buttonClicked);

}

void ValueComboBoxButtonWidget::setValue(QString new_value){
    int index = m_combobox->findText(new_value);
    if (index != -1) {
        m_combobox->setCurrentIndex(index);
    }
}

void ValueComboBoxButtonWidget::toggle_enable_button(bool enabled){
    m_button->setEnabled(enabled);
}
