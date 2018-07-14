#include "transform_menu.h"
#include "ui_transform_menu.h"

TransformMenu::TransformMenu( QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TransformOptions)
{
    ui->setupUi(this);
}

TransformMenu::~TransformMenu()
{
    delete ui;
}

void TransformMenu::on_pushButton_clicked()
{
    //emit a signal
}
