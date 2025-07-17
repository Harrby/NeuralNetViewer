
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_main_widget(new MainWidget())

{
    setCentralWidget(m_main_widget);
}

MainWindow::~MainWindow() = default;

