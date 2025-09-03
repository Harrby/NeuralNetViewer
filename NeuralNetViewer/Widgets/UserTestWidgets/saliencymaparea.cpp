
#include "saliencymaparea.h"

SaliencyMapArea::SaliencyMapArea(QWidget *parent)
    : QWidget{parent},
    image(grid_size, grid_size, QImage::Format_RGB888)
{
    image.fill(Qt::black);
    update();
    setFixedSize(grid_size * cell_size, grid_size * cell_size);
}


void SaliencyMapArea::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        qDebug() << "Clicked at " << event->pos().x() << event->pos().y();

        GetGridCoords(event->pos().x(), event->pos().y());
    }
}

void SaliencyMapArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Draw each logical pixel at the chosen cell_size          // ★
    for (int y = 0; y < grid_size; ++y)
        for (int x = 0; x < grid_size; ++x)
            painter.fillRect(x * cell_size, y * cell_size,
                             cell_size, cell_size,
                             image.pixelColor(x, y));          // ★
}

void SaliencyMapArea::GetGridCoords(int x, int y){
    const int gx = x / cell_size;
    const int gy = y / cell_size;
    if (gx < 0 || gx >= grid_size || gy < 0 || gy >= grid_size)
        return;
    qDebug() << "emitted clicked at signal";
    qDebug() << "clicked at:" << gx << gy;
    emit ClickedAt(gx, gy);
}

void SaliencyMapArea::setMap(const Eigen::VectorXf& saliencies){
    clear();
    float maxValue = saliencies.maxCoeff();
    float minValue = saliencies.minCoeff();

    qDebug() << "saliencies: min/max value" << minValue << maxValue;
    qDebug() << "saliencies size" << saliencies.rows() << saliencies.cols();

    for (int i =0; i < saliencies.size(); i++){
        int y = i /28;
        int x =i % 28;
        float v;
        if (maxValue != minValue){
        v =(saliencies[i] - minValue) / (maxValue - minValue);
        } else {
        v = 0.5;
        }

        QColor c = jetColor(v);
        image.setPixelColor(x, y, c);
    }

    update();

}

QColor SaliencyMapArea::jetColor(float v) {
    v = std::max(0.0f, std::min(1.0f, v));

    float r = std::min(std::max(1.5f - std::fabs(4.0f*v - 3.0f), 0.0f), 1.0f);
    float g = std::min(std::max(1.5f - std::fabs(4.0f*v - 2.0f), 0.0f), 1.0f);
    float b = std::min(std::max(1.5f - std::fabs(4.0f*v - 1.0f), 0.0f), 1.0f);

    return QColor(
        static_cast<int>(r * 255),
        static_cast<int>(g * 255),
        static_cast<int>(b * 255)
        );
}


void SaliencyMapArea::clear() {
    image.fill(Qt::black);
    update();
}

int SaliencyMapArea::getGridSize(){
    return grid_size;
};
