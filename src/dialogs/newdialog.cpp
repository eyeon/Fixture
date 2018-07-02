#include "newdialog.h"
#include "ui_newdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

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

void NewDialog::on_actionOk_clicked()
{
    // Needs a validation layer
    checkDimensionValidity(ui->heightTxt, "height");

    QString heightStr = ui->heightTxt->text();
    int height = heightStr.toDouble();

    checkDimensionValidity(ui->widthTxt, "width");

    QString widthStr = ui->widthTxt->text();
    int width = widthStr.toDouble();

    QString docName = ui->docNameVal->text();

    Document *document = createDocument(docName, width, height, Document::PIXELS, 72, Document::PPI);
    emit documentAvailable(document);
    this->close();
}
/**
 * @brief NewDialog::createDocument Creates a new document with the given params
 *
 * Processes the dimensions with specified units
 * @param docName
 * @param width
 * @param height
 * @param dimUnit
 * @param resolution
 * @param resUnit
 * @return
 */
Document* NewDialog::createDocument(QString docName, double width, double height,
                                 Document::DimensionUnit dimUnit, double resolution,
                                 Document::ResolutionUnit resUnit) const
{

    return new Document(docName,
                        width,
                        height,
                        dimUnit,
                        resolution,
                        resUnit);;
}

void NewDialog::on_actionCancel_clicked()
{
    this->close();
}



void NewDialog::on_widthTxt_editingFinished()
{
    checkDimensionValidity(ui->widthTxt, "width");
}

void NewDialog::showZeroErrorMessage(QString fieldName)
{
    QString errMsg = "Cannot set " + fieldName + " value less than 1";
    QMessageBox errDialogbox;
    errDialogbox.setText(errMsg);
    errDialogbox.exec();
}

void NewDialog::on_heightTxt_editingFinished()
{
    checkDimensionValidity(ui->heightTxt, "height");
}

void NewDialog::checkDimensionValidity(QLineEdit *field, QString fieldName)
{
    QString fieldStr = field->text();
    int fieldVal = fieldStr.toDouble();

    if (fieldVal < 1) {
        field->setText("");
        field->setFocus();
        showZeroErrorMessage(fieldName);
    }
}
