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
    for(int i=0;itr != _curItems.end();++itr,i++){
        takeItem(i);
        insertItem(i,itr->getListItem());
    }
}