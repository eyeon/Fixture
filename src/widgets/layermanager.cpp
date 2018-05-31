#include "layermanager.h"

class LayerItem : public QListWidgetItem
{
    LayerItem(QGraphicsItem *item, LayerType type)
    {

    }
};

LayerManager::LayerManager(QWidget *parent):
    QListWidget(parent)
{

}

void LayerManager::update(QGraphicsScene *scene, QVector<LayerType> typeList)
{

}
