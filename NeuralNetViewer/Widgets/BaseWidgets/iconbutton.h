
#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include<QPushButton>
#include <QEvent>
#include <array>


class IconButton : public QPushButton
{
    Q_OBJECT
public:
    IconButton(QString icon, std::array<QString, 3> background_color,int max_height, int max_width, QWidget *parent=nullptr);

private:
    std::array<QString, 3> background_colors;
    void onPressed();
    void onReleased();

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // ICONBUTTON_H
