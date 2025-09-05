
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_main_widget(new MainWidget())

{

    auto *shortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::toggleFullscreen);

    setCentralWidget(m_main_widget);
}

void MainWindow::toggleFullscreen(){
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

MainWindow::~MainWindow() = default;

