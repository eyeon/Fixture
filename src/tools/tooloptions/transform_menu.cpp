#include "transform_menu.h"
#include "ui_transform_menu.h"

TransformMenu::TransformMenu( QWidget *parent) :
    ToolMenu(parent),
    ui(new Ui::TransformOptions)
{
    ui->setupUi(this);
    ui->acceptBtn->setVisible(false);
    ui->rejectBtn->setVisible(false);
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

void TransformMenu::on_autoSelectCheck_stateChanged(int arg1)
{
    emit autoSelect(arg1 == Qt::Checked);
}

void TransformMenu::enterTransformMode(bool enter)
{
    ui->acceptBtn->setVisible(enter);
    ui->rejectBtn->setVisible(enter);
    ui->showTransfromCheck->setEnabled(!enter);
    ui->autoSelectCheck->setEnabled(!enter);
}

void TransformMenu::on_acceptBtn_clicked()
{
    emit changesAccepted(true);
    emit autoSelect(ui->autoSelectCheck->checkState() == Qt::Checked);
}

void TransformMenu::on_rejectBtn_clicked()
{
    emit changesAccepted(false);
    emit autoSelect(ui->autoSelectCheck->checkState() == Qt::Checked);
}
