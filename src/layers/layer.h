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
    enum LayerType {
        RASTER = QListWidgetItem::UserType,
        VECTOR,
        TEXT,
        ADJUSTMENT
    };

    Layer(QString name, LayerType type);

    ~Layer();
    inline void setName(QString &name){ _name = name; }
    inline QString getName() const { return _name; }
    inline LayerType getType() const { return _type; }
    inline void setType(LayerType type){ _type = type; }
    virtual void setSceneSelected(bool select) = 0;
    virtual void setLayerSelected(bool select) = 0;
    virtual void setZvalue(int z) = 0;
    virtual void setParent(QGraphicsItem *parent) = 0;
    virtual QPixmap getPixmap() const      = 0;
    virtual QPointF getPos() const         = 0;
    virtual void write(QDataStream&) const = 0;
    virtual void read(QDataStream&)        = 0;
    friend QDataStream& operator >> (QDataStream& ds, Layer &layer);
    friend QDataStream& operator << (QDataStream& ds, const Layer &layer);

    friend QDataStream& operator << (QDataStream& stream,
         const QList<Layer *>                   & l);
    friend QDataStream& operator >> (QDataStream& stream, QList<Layer *>& l);
    static Layer * create(const QString &name, LayerType type);
    virtual Layer * clone() const = 0;
protected:
    QString _name;
    LayerType _type;
};

#endif // LAYER_H
