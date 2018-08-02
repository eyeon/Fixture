#include "pan.h"

Pan::Pan(QWidget *parent):
    Tool(QIcon(":/tools/pan.svg"),"Pan Tool (H)",
         Qt::OpenHandCursor, Tool::PERCEPTION, Tool::PAN, parent)
{
    setShortcut(Qt::Key_H);
}

Pan::Pan(const Pan &other):
    Tool(QIcon(":/tools/pan.svg"),"Pan Tool (H)",
         Qt::OpenHandCursor, Tool::PERCEPTION, Tool::PAN)
{

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

void Pan::connectMenu()
{

}

Tool* Pan::clone() const
{
    return new Pan(*this);
}
