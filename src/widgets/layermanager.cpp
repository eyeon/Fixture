#include "layermanager.h"

LayerManager::LayerManager(QWidget *parent):
    QListWidget(parent)
{
    installEventFilter(this);
}

LayerManager::~LayerManager()
{
}

bool LayerManager::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::ChildRemoved){
        QList<int> changes;
        QList<Layer>::reverse_iterator itr = _curItems.rbegin();
        QList<Layer> items;

        for(int i=0;i<count();i++,++itr){
            int curPos = row(itr->getListItem());
            items.push_back(_curItems.at(curPos));
        }

        _curItems = items;
        emit itemschanged();

        return true;
    }

    return QListWidget::eventFilter(obj,event);
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
