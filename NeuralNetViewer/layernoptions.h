
#ifndef LAYERNOPTIONS_H
#define LAYERNOPTIONS_H

#include <QFrame>




class LayerNOptions : public QFrame
{
    Q_OBJECT
public:
    LayerNOptions(int n_layer, QWidget *parent = nullptr);
};

#endif // LAYERNOPTIONS_H
