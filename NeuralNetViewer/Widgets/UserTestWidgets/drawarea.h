
#ifndef DRAWAREA_H
#define DRAWAREA_H


#include <QWidget>
#include <QPainter>
#include <QMouseEvent>


class DrawArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawArea(QWidget *parent = nullptr);
    bool open_image(const QString& file_name);
    bool save_image(const QString& file_name, const char *file_format);
    void clear();

    void set_pen_width(int w);
    void set_feather(int f);
    int  get_pen_width() const;
    int get_feather() const;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    int pen_width = 1;
    int feather = 2;
    bool drawing = false;
    static const int grid_size = 28;
    static const int cell_size = 12;
    QImage image;

    void drawAt(int x, int y);



};

#endif // DRAWAREA_H
