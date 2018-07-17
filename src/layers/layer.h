#ifndef LAYER_H
#define LAYER_H

#include <QString>
#include <QImage>
#include <QDebug>
#include <QListWidgetItem>
#include <QGraphicsItem>
#include <QPixmap>

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

    inline QString getName() const { return _name; }
    inline LayerType getType() { return _type; }

    virtual void setSceneSelected(bool select) = 0;
    virtual void setLayerSelected(bool select) = 0;
    virtual void setZvalue(int z) = 0;
    virtual void setParent(QGraphicsItem *parent) = 0;
    virtual QPixmap getPixmap() const = 0;
    virtual QPointF getPos() const = 0;
    friend QDataStream & operator<< (QDataStream& out, const Layer *layer)
    {
        out << layer->getName() << layer->getPos() << layer->getPixmap();
        return out;
    }
private:
    QString _name;
    LayerType _type;
};

#endif // LAYER_H
