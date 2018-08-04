#include "tool.h"

Tool::Tool(QIcon ico, const QString &name, QCursor cur, ToolGroup group,
           ToolType type, QWidget * parent) :
    QAction(ico, name, parent), _cursor(cur), _name(name), _group(group), _type(
        type)
{
    setCheckable(true);
}

Tool::~Tool()
{ }
