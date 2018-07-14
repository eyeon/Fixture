#include "pan_menu.h"
#include "ui_pan_menu.h"

PanMenu::PanMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PanMenu)
{
    ui->setupUi(this);
}

PanMenu::~PanMenu()
{
    delete ui;
}
