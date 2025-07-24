
#include "iconbutton.h"

IconButton::IconButton(QString content, std::array<QString, 3> background_colors, int max_height, int max_width,  QWidget *parent)
    : QPushButton(parent),
    background_colors(background_colors)
{
    setMinimumSize(QSize(20, 20));

    if (QFile::exists(content)){
        setIcon(QIcon(content));
        setIconSize(QSize(static_cast<int>(this->width()*0.6), static_cast<int>(this->height()*0.75)));
        setMaximumSize(QSize(max_width, max_height));
    } else {
        setText(content);
        setStyleSheet("color: #ffffff;");
        QFontMetrics fm(font());
        int text_width = fm.horizontalAdvance(content);
        int padding = 40;  // extra space for padding/margins

        setMinimumWidth(text_width + padding);
    }
    setStyleSheet(QString("background-color: %1;"
                                "border-radius: 5px;"
                                "color: #ffffff;"
                                "border: 0px solid black;").arg(background_colors.at(0)));
    connect(this, &QPushButton::pressed, this, &IconButton::onPressed);
    connect(this, &QPushButton::released, this, &IconButton::onReleased);
}

void IconButton::enterEvent(QEnterEvent* event){
    setCursor(Qt::PointingHandCursor);
    setStyleSheet(QString("background-color: %1;"
                                "border-radius: 5px;"
                                "color: #ffffff;"
                                "border: 0px solid black;").arg(background_colors.at(1)));
    QPushButton::enterEvent(event);
}

void IconButton::leaveEvent(QEvent* event){
    unsetCursor();
    setStyleSheet(QString("background-color: %1;"
                          "border-radius: 5px;"
                          "color: #ffffff;"
                          "border: 0px solid black;").arg(background_colors.at(0)));
    QPushButton::leaveEvent(event);
}

void IconButton::resizeEvent(QResizeEvent* event){
    if (!this->icon().isNull()){
        setIconSize(QSize(static_cast<int>(this->width()*0.6), static_cast<int>(this->height()*0.75)));
    }
    QPushButton::resizeEvent(event);
}

void IconButton::onPressed(){
    setStyleSheet(QString("background-color: %1;"
                          "border-radius: 5px;"
                          "color: #ffffff;"
                          "border: 0px solid black;").arg(background_colors.at(2)));
}

void IconButton::onReleased(){
    setStyleSheet(QString("background-color: %1;"
                          "border-radius: 5px;"
                          "color: #ffffff;"
                          "border: 0px solid black;").arg(background_colors.at(1)));
}


