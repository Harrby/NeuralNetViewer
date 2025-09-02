
#include <QApplication>
#include <QWidget>
#include <QFontDatabase>


#include "mainwindow.h"
#include "mnistinputwidget.h"
#include "mnistuseroutputwidget.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int id = QFontDatabase::addApplicationFont(":/fonts/Inter/Inter-VariableFont_opsz,wght.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).value(0);
    QFont inter(family, 14);
    app.setFont(inter);

    //ValueSliderWidget *slider = new ValueSliderWidget("neurons", 0.00001, 1000, Slider::Logarithmic, 1000, nullptr);
    //IconButton *vcbw = new IconButton(QString(":/images/images/plus.png"),{"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"}, 500, 500);

    MainWindow *vcbw = new MainWindow();

    //MNISTUserOutputWidget *da = new MNISTUserOutputWidget();

    vcbw->show();
    return app.exec();
}
