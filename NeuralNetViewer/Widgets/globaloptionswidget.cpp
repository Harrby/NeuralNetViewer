
#include "globaloptionswidget.h"
#include "qgridlayout.h"

GlobalOptionsWidget::GlobalOptionsWidget(QWidget *parent)
    : QFrame(parent),
    m_cb_optimiser(new ValueComboBoxWidget("Optimiser", QStringList{"SGD", "Adam", "RMSProp"}, this)),
    m_cb_loss_function(new ValueComboBoxWidget("Loss Function", QStringList{"CCE"}, this)),
    m_s_learning_rate(new ValueSliderWidget("Learning Rate", 1e-6, 1.0, Slider::Logarithmic, 1000, this)),
    m_s_epochs(new ValueSliderWidget("Epochs", 0, 1000, Slider::Linear, 1000, this)),
    m_title(new QLabel("Global Options", this))
{
    setStyleSheet(".GlobalOptionsWidget{background-color: #302B2B;"
                  "                     border 1px solid #2A2626;"
                  "                     border-radius:4px; }"
                  );

    m_title->setStyleSheet("color: white;");


    QGridLayout *grid_layout = new QGridLayout;
    grid_layout->addWidget(m_cb_optimiser, 0, 0);
    grid_layout->addWidget(m_cb_loss_function, 0, 1);
    grid_layout->addWidget(m_s_learning_rate, 1, 0);
    grid_layout->addWidget(m_s_epochs, 1, 1);
    grid_layout->setVerticalSpacing(0);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(m_title);
    main_layout->addLayout(grid_layout);


}

