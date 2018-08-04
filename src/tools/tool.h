#ifndef TOOL_H
#define TOOL_H

#include <QAction>
#include <QGraphicsSceneMouseEvent>

#include "../layers/layer.h"

class Tool : public QAction
{
public:
    enum ToolGroup {
        SELECTION,
        CREATION,
        MODIFICATION,
        PERCEPTION
    };

    enum ToolType {
        TRANSFORM,
        PAN
    };

    Tool(QIcon ico, const QString &name, QCursor cur, ToolGroup group,
         ToolType type, QWidget * parent = 0);
    ~Tool();

    inline const QCursor getToolCursor(){ return _cursor; }
    inline const QString getToolName(){ return _name; }
    inline ToolGroup getToolGroup(){ return _group; }
    inline ToolType getToolType(){ return _type; }

public:
    virtual void move(QGraphicsSceneMouseEvent * event)    = 0;
    virtual void press(QGraphicsSceneMouseEvent * event)   = 0;
    virtual void release(QGraphicsSceneMouseEvent * event) = 0;
    virtual QWidget * getToolMenu() = 0;
    virtual Tool * clone() const    = 0;

private:
    QCursor _cursor;
    QString _name;
    ToolGroup _group;
    ToolType _type;
    void drawRectItem();
    // virtual void connectMenu() = 0;

protected:
    QWidget * _menu;
    bool _menuExists = false;
};
template <>
inline Tool * QSharedDataPointer<Tool>::clone()
{
    return d->clone();
}

#endif // TOOL_H
