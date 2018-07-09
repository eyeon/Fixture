#include "pan.h"

Pan::Pan(QWidget *parent):
    Tool(QIcon(":/tools/pan.svg"),"Pan Tool (H)",
         Qt::OpenHandCursor, Tool::Pan,parent)
{
    setShortcut(Qt::Key_H);
}

Pan::~Pan()
{

}
