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
    delete document;
}

void NewDialog::on_actionOk_clicked()
{
    // Needs a validation layer
    QString heightStr = ui->heightVal->text();
    double height = heightStr.toDouble();

    QString widthStr = ui->widthVal->text();
    double width = widthStr.toDouble();

    QString docName = ui->docNameVal->text();

    document = new Document(docName,
             width,
             height,
             Document::PIXELS,
             72,
             Document::PPI);
    emit documentAvailable(document);
    this->close();
}

Document* NewDialog::getDocument() const
{
    return document;
}

void NewDialog::on_actionCancel_clicked()
{
    this->close();
}
