#include "newdialog.h"
#include "ui_newdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>

NewDialog::NewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialog)
{
    ui->setupUi(this);
    ui->actionBtnsContainer->setAlignment(Qt::AlignTop);
}

NewDialog::~NewDialog()
{
    delete ui;
}
