#ifndef LAYER_H
#define LAYER_H

#include <QString>
#include <QImage>
#include <QListWidgetItem>
#include <QGraphicsItem>

class Layer : public QListWidgetItem
{
public:
    enum LayerType{
        RasterLayer,
        VectorLayer,
        TextLayer,
        AdjustmentLayer
    };

    Layer(QString name, LayerType type);

    ~Layer();

    inline QString getName() { return _name; }
    inline LayerType getType() { return _type; }

    virtual void setSceneSelected(bool select) = 0;
    virtual void setLayerSelected(bool select) = 0;
    virtual void setZvalue(int z) = 0;

private:
    QString _name;
    LayerType _type;
};

#endif // LAYER_H
