#include "transform_menu.h"
#include "ui_transform_menu.h"

TransformMenu::TransformMenu( QWidget *parent) :
    ToolMenu(parent),
    ui(new Ui::TransformOptions)
{
    ui->setupUi(this);
    addStyleSheet();
}

TransformMenu::~TransformMenu()
{
    delete ui;
}
