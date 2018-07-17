#ifndef DRAWING_H
#define DRAWING_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QImageReader>
#include <QWheelEvent>
#include <QScrollBar>
#include <QObject>
#include <QWidget>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

#include "../layers/rasterlayer.h"
#include "../tools/tool.h"

class Drawing : public QGraphicsScene
{
    Q_OBJECT

public:
    Drawing(QWidget *widget, int width, int height);
    ~Drawing();
    inline QGraphicsItem* getParentItem(){ return _parentItem; }
    inline void setTool(Tool* tool){_tool = tool;}

private:
    int _height,_width;
    QGraphicsItem *_parentItem;
    Tool *_tool;

    void dragEnterEvent(QGraphicsSceneDragDropEvent *e);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *e);
    void dropEvent(QGraphicsSceneDragDropEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void importAvailable(const QString &fileName);

};

#endif // DRAWING_H
