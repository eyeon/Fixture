#include "layermanager.h"

LayerManager::LayerManager(QWidget *parent):
    QListWidget(parent)
{
}

LayerManager::~LayerManager()
{
}

void LayerManager::updateItems(QList<Layer> items)
{
    _curItems = items;
    QList<Layer>::iterator itr = _curItems.begin();
    for(;itr != _curItems.end();++itr){
        addItem(itr->getListItem());
    }
}
