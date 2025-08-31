
#include "drawarea.h"

DrawArea::DrawArea(QWidget *parent)
    : QWidget(parent),
    image(grid_size, grid_size, QImage::Format_Grayscale8)
{
    image.fill(Qt::black);
    setFixedSize(grid_size * cell_size, grid_size * cell_size);

}



void DrawArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Draw each logical pixel at the chosen cell_size          // ★
    for (int y = 0; y < grid_size; ++y)
        for (int x = 0; x < grid_size; ++x)
            painter.fillRect(x * cell_size, y * cell_size,
                             cell_size, cell_size,
                             image.pixelColor(x, y));          // ★
}

void DrawArea::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        drawing = true;
        drawAt(event->pos().x(), event->pos().y());
    }
}

void DrawArea::mouseMoveEvent(QMouseEvent* event){
    if((event->buttons() & Qt::LeftButton) && drawing){
        drawAt(event->pos().x(), event->pos().y());
    }
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event){
    drawing = false;
}

void DrawArea::drawAt(int x, int y)
{
    const int gx = x / cell_size;
    const int gy = y / cell_size;
    if (gx < 0 || gx >= grid_size || gy < 0 || gy >= grid_size)
        return;

    const int solidR   = pen_width / 2;
    const int featherR = solidR + feather;

    QPainter p(&image);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setCompositionMode(QPainter::CompositionMode_SourceOver);


    QRadialGradient g(QPointF(gx + 0.5, gy + 0.5), featherR);
    g.setColorAt(0.0, QColor(255, 255, 255, 255));
    g.setColorAt(qreal(solidR) / featherR,
                 QColor(255, 255, 255, 255));
    g.setColorAt(1.0, QColor(255, 255, 255,   0));
    p.setBrush(g);
    p.setPen(Qt::NoPen);
    p.drawEllipse(QPointF(gx + 0.5, gy + 0.5), featherR, featherR);


    const int d = featherR;
    update(QRect((gx - d) * cell_size,
                 (gy - d) * cell_size,
                 (2 * d + 1) * cell_size,
                 (2 * d + 1) * cell_size));
}
void DrawArea::clear() {
    image.fill(Qt::black);
    update();
}


void DrawArea::set_pen_width(int w){
    pen_width = qBound(1, w, grid_size);
};
int  DrawArea::get_pen_width()   const{
    return pen_width;
};
void DrawArea::set_feather(int f){
    feather = qMax(0, f);
}

int DrawArea::get_feather() const{
    return feather;
}
