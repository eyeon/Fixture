#include "transform.h"

Transform::Transform(QWidget* parent):
    Tool(QIcon(":/tools/select.svg"),"Transform Tool (V)",
         QCursor(QIcon(":/tools/select.svg").pixmap(QSize(15,15)),0,0),
         Tool::Transform,parent)
{
    setShortcut(Qt::Key_V);
}

Transform::~Transform()
{

}
