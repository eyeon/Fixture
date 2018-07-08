#include "newdialog.h"
#include "ui_newdialog.h"

NewDialog::NewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialog)
{
    ui->setupUi(this);
    ui->actionBtnsContainer->setAlignment(Qt::AlignTop);

    initPresetList();
    ui->docTypeCombo->addItems(QStringList(docTypes.values()));
    ui->docTypeCombo->setCurrentIndex(DocType::DEFAULT);

    initDimensionUnitList();

    ui->widthUnitCombo->addItems(QStringList(dimensions.values()));
    ui->widthUnitCombo->setCurrentIndex(Canvas::DimensionUnit::PIXELS);

    ui->heightUnitCombo->addItems(QStringList(dimensions.values()));
    ui->heightUnitCombo->setCurrentIndex(Canvas::DimensionUnit::PIXELS);

    connect(ui->docTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(switchDocType(int)));
    connect(ui->widthUnitCombo, SIGNAL(currentIndexChanged(int)), ui->heightUnitCombo, SLOT(setCurrentIndex(int)));
    connect(ui->heightUnitCombo, SIGNAL(currentIndexChanged(int)), ui->widthUnitCombo, SLOT(setCurrentIndex(int)));
    connect(ui->presetCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(displayPreset(QString)));
}

NewDialog::~NewDialog()
{
    delete ui;
}

void NewDialog::initDimensionUnitList()
{
    dimensions.insert(Canvas::DimensionUnit::PIXELS, "Pixels");
    dimensions.insert(Canvas::DimensionUnit::INCHES, "Inches");
    dimensions.insert(Canvas::DimensionUnit::CENTIMETERS, "Centimeters");
}

void NewDialog::initPresetList()
{
    docTypes.insert(DocType::DEFAULT, "Fixture Default");
    docTypes.insert(DocType::INTERNATIONAL, "International");
    docTypes.insert(DocType::US_PAPER, "US Paper");
    docTypes.insert(DocType::CUSTOM, "Custom");
}
QMap<QString, NewDialog::PageSize> NewDialog::getInternationalList()
{
    QMap<QString, PageSize> presets;

    PageSize A1 {23.39, 33.11, Canvas::INCHES};
    PageSize A2 {16.54, 23.39, Canvas::INCHES};
    PageSize A3 {11.69, 16.54, Canvas::INCHES};
    PageSize A4 {8.27, 11.69, Canvas::INCHES};
    PageSize A5 {5.83, 8.27, Canvas::INCHES};

    presets.insert("A1", A1);
    presets.insert("A2", A2);
    presets.insert("A3", A3);
    presets.insert("A4", A4);
    presets.insert("A5", A5);

    return presets;
}

void NewDialog::switchDocType(int index)
{
    switch (index) {
    case DocType::INTERNATIONAL:
        ui->presetCombo->setDisabled(false);
        currPreset = getInternationalList();
        ui->presetCombo->addItems(QStringList(currPreset.keys()));
        break;
    default:
        ui->presetCombo->clear();
        ui->presetCombo->setDisabled(true);
        displaySizeContents(NewDialog::Default);
        break;
    }
}

void NewDialog::displayPreset(QString presetKey)
{
    PageSize size = currPreset.value(presetKey);
    displaySizeContents(size);
}

void NewDialog::displaySizeContents(NewDialog::PageSize size)
{
    ui->widthTxt->setText(QString::number(size.width));
    ui->heightTxt->setText(QString::number(size.height));
    ui->widthUnitCombo->setCurrentIndex(size.unit);
    ui->heightUnitCombo->setCurrentIndex(size.unit);
}

void NewDialog::on_actionOk_clicked()
{
    // Needs a validation layer
    try {
        _dimensionUnit = (Canvas::DimensionUnit) ui->widthUnitCombo->currentIndex();
        _resolution = (int) getDoubleValue(ui->resTxt);

        ui->heightTxt->setFocus();
        int height = getPixelValue(ui->heightTxt);

        ui->widthTxt->setFocus();
        int width = getPixelValue(ui->widthTxt);
        QString docName = ui->docNameVal->text();

        Canvas *canvas = createCanvas(docName, width, height, _dimensionUnit, _resolution, Canvas::PPI);

        emit canvasAvailable(canvas);
        this->close();

    } catch (const QString msg) {
        showZeroErrorMessage(msg);
        return;
    }
}
/**
 * @brief NewDialog::createCanvas Creates a new canvas with the given params
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
        checkDimensionValidity(getDoubleValue(ui->widthTxt));
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
        checkDimensionValidity(getDoubleValue(ui->heightTxt));
    }
    catch (const QString msg) {        
        ui->heightTxt->setFocus();
        showZeroErrorMessage(msg);
    }
}
// This part needs to be heavily improved.
void NewDialog::checkDimensionValidity(double fieldVal)
{
    if (fieldVal < 1) {
        QString error = "Cannot set dimension value less than 1";
        throw error;
    }
}

double NewDialog::getDoubleValue(QLineEdit *fieldVal)
{
    QString fieldStr = fieldVal->text();
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
