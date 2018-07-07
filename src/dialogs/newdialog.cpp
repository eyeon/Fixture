#include "newdialog.h"
#include "ui_newdialog.h"

NewDialog::NewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialog)
{
    ui->setupUi(this);
    ui->actionBtnsContainer->setAlignment(Qt::AlignTop);
    initDimensionUnitList();

    ui->widthUnitCombo->addItems(QStringList(dimensions->keys()));
    ui->widthUnitCombo->setCurrentIndex(dimensions->size() - 1);

    ui->heightUnitCombo->addItems(QStringList(dimensions->keys()));
    ui->heightUnitCombo->setCurrentIndex(dimensions->size() - 1);

    connect(ui->widthUnitCombo, SIGNAL(currentIndexChanged(int)), ui->heightUnitCombo, SLOT(setCurrentIndex(int)));
    connect(ui->heightUnitCombo, SIGNAL(currentIndexChanged(int)), ui->widthUnitCombo, SLOT(setCurrentIndex(int)));
}

NewDialog::~NewDialog()
{
    delete ui;
}

void NewDialog::initDimensionUnitList()
{
    dimensions->insert("Pixels", Canvas::DimensionUnit::PIXELS);
    dimensions->insert("Inches", Canvas::DimensionUnit::INCHES);
    dimensions->insert("Centimeters", Canvas::DimensionUnit::CENTIMETERS);

}
void NewDialog::on_actionOk_clicked()
{
    // Needs a validation layer
    try {

        _dimensionUnit = dimensions->value(ui->widthUnitCombo->currentText());
        _resolution = (int) getDoubleValue(ui->resTxt);

        ui->heightTxt->setFocus();
        int height = getPixelValue(ui->heightTxt);

        ui->widthTxt->setFocus();
        int width = getPixelValue(ui->widthTxt);

        QString docName = ui->docNameVal->text();

        Canvas *canvas = createCanvas(docName, width, height, _dimensionUnit, _resolution, Canvas::PPI);
        // test
        qDebug() << "Canvas data: ";
        qDebug() << "Width: " << canvas->getWidth() <<  "Height: " << canvas->getHeight();
        qDebug() << "Dimension Unit" << canvas->getDimensionUnit() << "Resolution: " << canvas->getResolution();
        emit canvasAvailable(canvas);
        this->close();

    }
    catch (const QString msg) {
        // We are probably doing it wrong
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
Canvas* NewDialog::createCanvas(QString docName, double width, double height,
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
        checkDimensionValidity(ui->widthTxt);
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
       checkDimensionValidity(ui->heightTxt);
    }
    catch (const QString msg) {        
        ui->heightTxt->setFocus();
        showZeroErrorMessage(msg);
    }
}
// This part needs to be heavily improved.
void NewDialog::checkDimensionValidity(QLineEdit *field)
{
    QString fieldStr = field->text();
    int fieldVal = fieldStr.toDouble();

    if (fieldVal < 1) {
        QString error = "Cannot set dimension value less than 1";
        throw error;
    }
}

double NewDialog::getDoubleValue(QLineEdit *field)
{
    QString fieldStr = field->text();
    return fieldStr.toDouble();
}

int NewDialog::getPixelValue(QLineEdit *field)
{
    double val = getDoubleValue(field);

    switch(_dimensionUnit) {
    case Canvas::DimensionUnit::INCHES:
        return val * _resolution;
    case Canvas::DimensionUnit::CENTIMETERS:
        return val * _resolution * 2.54;
    default:
        return val;
    }
}
