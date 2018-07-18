#ifndef RASTERLAYER_H
#define RASTERLAYER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsScene>

#include "layer.h"

class RasterLayer : public Layer, public QGraphicsPixmapItem
{
public:
    RasterLayer(const QString &name, const QImage &image);
    RasterLayer();
    ~RasterLayer();

    void setLocked(bool lock);
    void setSceneSelected(bool select);
    void setLayerSelected(bool select);
    void setZvalue(int z);
    void setParent(QGraphicsItem *parent);
    inline QPixmap getPixmap() const { return pixmap(); }
    inline QPointF getPos() const { return QGraphicsPixmapItem::pos(); }
    inline void setLayerPos(QPointF pos) { setPos(pos);}
    inline void setLayerPixmap(QPixmap pixmap) { setPixmap(pixmap); }

    void write(QDataStream&) const;
    void read(QDataStream&);

protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QImage _image;
};

#endif // RASTERLAYER_H
