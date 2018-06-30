#ifndef LAYER_H
#define LAYER_H

#include <QListWidgetItem>

enum class LayerType{
    RasterLayer,
    VectorLayer,
    TextLayer,
    AdjustmentLayer
};

class Layer: public QListWidgetItem
{
public:
    Layer(QListWidget *widget);
    ~Layer();
};

#endif // LAYER_H
