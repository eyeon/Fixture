#include "layermanager.h"

LayerManager::LayerManager(QWidget *parent):
    QListWidget(parent)
{
}

LayerManager::~LayerManager()
{
}

void LayerManager::update(QList<Layer> items)
{
    QList<Layer>::iterator itr = items.begin();
    _curItems = items;
    for(;itr != items.end();++itr){
        addItem(itr->getListItem());
    }
}
