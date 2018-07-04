#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QListWidget>

#include "../items/layer.h"

class LayerManager : public QListWidget
{
public:
    LayerManager(QWidget *parent=0);
    ~LayerManager();

    void updateItems(QList<Layer> items);

private:
    QList<Layer> _curItems;
};

#endif // LAYERMANAGER_H
