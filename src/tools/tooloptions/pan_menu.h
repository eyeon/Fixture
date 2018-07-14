#ifndef PAN_MENU_H
#define PAN_MENU_H

#include <QFrame>

namespace Ui {
class PanMenu;
}

class PanMenu : public QFrame
{
    Q_OBJECT

public:
    explicit PanMenu(QWidget *parent = 0);
    ~PanMenu();

private:
    Ui::PanMenu *ui;
};

#endif // PAN_MENU_H
