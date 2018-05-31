#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsItem>

enum LayerType{
    RasterLayer,
    VectorLayer,
    TextLayer,
    AdjustmentLayer
};

class LayerItem;

class LayerManager : public QListWidget
{
public:
    LayerManager(QWidget *parent=0);
    void update(QGraphicsScene *scene, QVector<LayerType> typeList);

private:
    QVector<LayerItem> _items;
};

#endif // LAYERMANAGER_H
