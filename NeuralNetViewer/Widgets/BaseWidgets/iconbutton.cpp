
#include "iconbutton.h"

IconButton::IconButton(QString icon, std::array<QString, 3> background_colors, int max_height, int max_width, QWidget *parent)
    : QPushButton(parent),
    background_colors(background_colors)
{
    this->setMinimumSize(QSize(20, 20));
    this->setMaximumSize(QSize(max_width, max_height));
    this->setIcon(QIcon(icon));
    this->setIconSize(QSize(static_cast<int>(this->width()*0.6), static_cast<int>(this->height()*0.75)));
    this-> setStyleSheet(QString("background-color: %1;"
                                "border-radius: 5px;"
                                "border: 0px solid black;").arg(background_colors.at(0)));
    connect(this, &QPushButton::pressed, this, &IconButton::onPressed);
    connect(this, &QPushButton::released, this, &IconButton::onReleased);
}

void IconButton::enterEvent(QEnterEvent* event){
    this->setCursor(Qt::PointingHandCursor);
    this -> setStyleSheet(QString("background-color: %1;"
                                "border-radius: 5px;"
                                "border: 0px solid black;").arg(background_colors.at(1)));
    QPushButton::enterEvent(event);
}

void IconButton::leaveEvent(QEvent* event){
    this->unsetCursor();
    this -> setStyleSheet(QString("background-color: %1;"
                                "border-radius: 5px;"
                                "border: 0px solid black;").arg(background_colors.at(0)));
    QPushButton::leaveEvent(event);
}

void IconButton::resizeEvent(QResizeEvent* event){
    this->setIconSize(QSize(static_cast<int>(this->width()*0.6), static_cast<int>(this->height()*0.75)));
    QPushButton::resizeEvent(event);
}

void IconButton::onPressed(){
    this -> setStyleSheet(QString("background-color: %1;"
                                "border-radius: 5px;"
                                "border: 0px solid black;").arg(background_colors.at(2)));
}

void IconButton::onReleased(){
    this -> setStyleSheet(QString("background-color: %1;"
                                "border-radius: 5px;"
                                "border: 0px solid black;").arg(background_colors.at(1)));
}


