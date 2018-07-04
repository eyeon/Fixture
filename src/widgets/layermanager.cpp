#include "layermanager.h"

#include <QDebug>

LayerManager::LayerManager(QWidget *parent):
    QListWidget(parent)
{
    setDragDropMode(QAbstractItemView::InternalMove);
}

LayerManager::~LayerManager()
{
}

void LayerManager::updateItems(QList<Layer> items)
{
    int max = count();
    for(int i=max-1;i>=0;i--){
        takeItem(i);
    }

    _curItems = items;
    QList<Layer>::reverse_iterator itr = _curItems.rbegin();
    for(int i=0;itr != _curItems.rend();++itr,i++){
        insertItem(i,itr->getListItem());
    }
}
