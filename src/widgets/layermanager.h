#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QListWidget>
#include <QEvent>
#include <QFile>
#include <QPainter>

#include "../layers/layer.h"

class LayerManager : public QListWidget
{
    Q_OBJECT
public:
    LayerManager(QWidget *parent = nullptr);
    ~LayerManager();

    void updateItems(QList<Layer *> items);
    QList<QListWidgetItem *> getitems();

signals:
    void itemschanged();

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    QList<Layer *> _curItems;
};

#endif // LAYERMANAGER_H
