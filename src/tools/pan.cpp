#include "pan.h"

/**
 * @brief Pan::Pan Constructs a Pan Tool
 * @param parent
 */
Pan::Pan(QWidget *parent) :
    Tool(QIcon(":/tools/pan.svg"), "Pan Tool (H)",
         Qt::OpenHandCursor, Tool::PERCEPTION, Tool::PAN, parent)
{
    setShortcut(Qt::Key_H);
}

/**
 * @brief Pan::Pan
 * @param other
 */
Pan::Pan(const Pan &other) :
    Tool(QIcon(":/tools/pan.svg"), "Pan Tool (H)",
         Qt::OpenHandCursor, Tool::PERCEPTION, Tool::PAN)
{ }

/**
 * @brief Pan::~Pan
 */
Pan::~Pan()
{ }

/**
 * @brief Pan::move dummy function for now, functionality handled by paintwidget itself
 * @param event
 */
void Pan::move(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

/**
 * @brief Pan::press dummy function for now, functionality handled by paintwidget itself
 * @param event
 */
void Pan::press(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

/**
 * @brief Pan::release dummy function for now, functionality handled by paintwidget itself
 * @param event
 */
void Pan::release(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

/**
 * @brief Pan::getToolMenu returns the tool menu associated with the Pan Tool
 * @return
 */
QWidget * Pan::getToolMenu()
{
    PanMenu *menu = new PanMenu();
    return menu;
}

/**
 * @brief Pan::connectMenu
 */
void Pan::connectMenu()
{ }

/**
 * @brief Pan::clone
 * @return
 */
Tool * Pan::clone() const
{
    return new Pan(*this);
}
