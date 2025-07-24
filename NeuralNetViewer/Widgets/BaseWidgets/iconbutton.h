
#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include<QPushButton>
#include <QEvent>
#include <array>
#include <QFile>

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    IconButton(QString content, std::array<QString, 3> background_color,int max_height, int max_width,  QWidget *parent=nullptr);

private:
    std::array<QString, 3> background_colors;
    void onPressed();
    void onReleased();
    float m_ratio_x =0.6f;
    float m_ratio_y =0.75f;

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // ICONBUTTON_H
