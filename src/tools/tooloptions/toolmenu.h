#ifndef TOOLMENU_H
#define TOOLMENU_H

#include <QFrame>
#include <QFile>

class ToolMenu : public QFrame
{
    Q_OBJECT

public:
    ToolMenu(QWidget * parent);

protected:
    void addStyleSheet();
};

#endif // TOOLMENU_H
