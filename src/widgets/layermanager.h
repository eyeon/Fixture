#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QIcon>
#include "paintwidget.h"

enum class LayerType{
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

private:
    QList<LayerItem> *_itemsTypes;
    QList<QGraphicsItem> *_items;
};

#endif // LAYERMANAGER_H
