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
        RASTER,
        VECTOR,
        TEXT,
        ADJUSTMENT
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
    virtual void setLayerPixmap(QPixmap pixmap) = 0;
    virtual void setLayerPos(QPointF pos) = 0;
    friend QDataStream & operator>> (QDataStream& in, Layer *&layer)
    {
        QString name;
        QPointF pos;
        QPixmap pixmap;
        in >> name >> pos >> pixmap;

        qDebug() << name;
        qDebug() << in;
        return in;
    }

private:
    QString _name;
    LayerType _type;
};

#endif // LAYER_H
