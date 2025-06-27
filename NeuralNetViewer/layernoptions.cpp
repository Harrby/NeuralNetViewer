
#include "layernoptions.h"

LayerNOptions::LayerNOptions(int n_layer, QWidget *parent)
    : QFrame(parent)
{
    int id = n_layer;
    setStyleSheet("background-color: #302B2B;");
}

