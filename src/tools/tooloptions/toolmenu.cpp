#include "toolmenu.h"

ToolMenu::ToolMenu(QWidget *parent) :
    QFrame(parent)
{ }

void ToolMenu::addStyleSheet()
{
    QFile styleFile(":/styles/tool-menu.qss");
    styleFile.open(QFile::ReadOnly);

    QString style(styleFile.readAll() );
    setStyleSheet(style);
}
