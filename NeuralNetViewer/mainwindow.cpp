
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a button and set it as the central widget
    myButton = new QPushButton("Click me", this);
    setCentralWidget(myButton);

    // Connect a signal to a lambda for demonstration
    connect(myButton, &QPushButton::clicked, this, []() {
        qDebug("Button clicked!");
    });
}

MainWindow::~MainWindow()
{
    // QPushButton will be deleted automatically because it's a child of this
}

