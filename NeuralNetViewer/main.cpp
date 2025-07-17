
#include "slider.h"
#include <QApplication>
#include <QWidget>
#include "valuesliderwidget.h"
#include <QFontDatabase>
#include "combobox.h"
#include "valuecomboboxwidget.h"
#include "globaloptionswidget.h"
#include "checkbox.h"
#include "layeroptions.h"
#include "iconbutton.h"
#include "layerscrollarea.h"
#include "networkconfigwidget.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int id = QFontDatabase::addApplicationFont(":/fonts/Inter/Inter-VariableFont_opsz,wght.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).value(0);
    QFont inter(family, 16);
    app.setFont(inter);

    //ValueSliderWidget *slider = new ValueSliderWidget("neurons", 0.00001, 1000, Slider::Logarithmic, 1000, nullptr);
    //IconButton *vcbw = new IconButton(QString(":/images/images/plus.png"),{"rgba(48, 43, 43, 255)", "rgba(48, 43, 43, 150)", "rgba(48, 43, 43, 70)"}, 500, 500);

    MainWindow *vcbw = new MainWindow();

    vcbw->show();
    return app.exec();
}
