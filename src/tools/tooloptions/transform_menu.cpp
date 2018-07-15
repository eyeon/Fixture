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

void TransformMenu::on_showTransfromCheck_stateChanged(int arg1)
{
    emit showTransform(arg1 == Qt::Checked);
}
