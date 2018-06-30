#include "layermanager.h"

class LayerItem : public QListWidgetItem
{
public:
    LayerItem(QGraphicsPixmapItem *item, LayerType type)
    {
        if(type == LayerType::RasterLayer){
            _icon = QIcon(item->pixmap());
        }

        setIcon(_icon);
    }

    QIcon _icon;
};

LayerManager::LayerManager(QWidget *parent):
    QListWidget(parent)
{

}

