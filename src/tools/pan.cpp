#include "pan.h"

Pan::Pan(QWidget *parent):
    Tool(QIcon(":/tools/pan.svg"),"Pan Tool (H)",
         Qt::OpenHandCursor, Tool::PERCEPTION, Tool::PAN, parent)
{
    setShortcut(Qt::Key_H);
}

Pan::~Pan()
{

}
void Pan::move(QMouseEvent *event)
{

}
void Pan::press(QMouseEvent *event)
{

}
void Pan::release(QMouseEvent *event)
{

}

QWidget* Pan::getToolMenu()
{
    PanMenu *menu = new PanMenu();
    return menu;
}
