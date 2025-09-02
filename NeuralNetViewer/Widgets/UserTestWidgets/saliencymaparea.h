
#ifndef SALIENCYMAPAREA_H
#define SALIENCYMAPAREA_H


#include <QWidget>
#include <QMouseEvent>
#include <Eigen/Dense>
#include <QPainter>

class SaliencyMapArea : public QWidget
{
    Q_OBJECT
public:
    explicit SaliencyMapArea(QWidget *parent = nullptr);
    void setMap(const Eigen::VectorXf& saliencies);
    void clear();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *) override;



private:
    static const int grid_size = 28;
    static const int cell_size = 12;
    QImage image;

    void GetGridCoords(int x, int y);
    QColor jetColor(float v);

signals:
    void ClickedAt(int x, int y);

};

#endif // SALIENCYMAPAREA_H
