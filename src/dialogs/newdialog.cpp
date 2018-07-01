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

void NewDialog::on_actionOk_clicked()
{
    // Needs a validation layer
    QString heightStr = ui->heightVal->text();
    double height = heightStr.toDouble();

    QString widthStr = ui->widthVal->text();
    double width = widthStr.toDouble();

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
