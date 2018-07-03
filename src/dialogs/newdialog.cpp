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
    try {

        ui->heightTxt->setFocus();
        int height = getIntValue(ui->heightTxt);

        ui->widthTxt->setFocus();
        int width = getIntValue(ui->widthTxt);

        QString docName = ui->docNameVal->text();

        Canvas *canvas = createDocument(docName, width, height, Canvas::PIXELS, 72, Canvas::PPI);
        emit canvasAvailable(canvas);
        this->close();

    }
    catch (const QString msg) {
        showZeroErrorMessage(msg);
        return;
    }
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
Canvas* NewDialog::createDocument(QString docName, double width, double height,
                                 Canvas::DimensionUnit dimUnit, double resolution,
                                 Canvas::ResolutionUnit resUnit) const
{

    return new Canvas(docName,
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
    try {
        getIntValue(ui->widthTxt);
    }
    catch (const QString msg) {
        ui->widthTxt->setFocus();
        showZeroErrorMessage(msg);
    }
}

void NewDialog::showZeroErrorMessage(QString errMsg)
{
    QMessageBox errDialogbox;
    errDialogbox.setText(errMsg);
    errDialogbox.exec();
}

void NewDialog::on_heightTxt_editingFinished()
{
    try {
       getIntValue(ui->heightTxt);
    }
    catch (const QString msg) {        
        ui->heightTxt->setFocus();
        showZeroErrorMessage(msg);
    }
}

void NewDialog::checkDimensionValidity(int fieldVal)
{
    if (fieldVal < 1) {
        QString error = "Cannot set dimension value less than 1";
        throw error;
    }
}

int NewDialog::getIntValue(QLineEdit *field)
{
    QString fieldStr = field->text();
    int fieldVal = fieldStr.toDouble();
    checkDimensionValidity(fieldVal);

    return fieldVal;
}
