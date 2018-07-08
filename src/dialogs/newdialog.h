#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>

#include "../model/canvas.h"

namespace Ui {
class NewDialog;
}

class NewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDialog(QWidget *parent = 0);
    ~NewDialog();

signals:
    void canvasAvailable(const Canvas *canvas);

private slots:
    void on_actionOk_clicked();
    void on_actionCancel_clicked();
    void on_widthTxt_editingFinished();
    void on_heightTxt_editingFinished();

    void switchDocType(int index);
    void displayPreset(QString presetKey);
private:
    struct PageSize
    {
        double width;
        double height;
        Canvas::DimensionUnit unit;
    }
    Default { 600, 600, Canvas::DimensionUnit::PIXELS};

    enum DocType
    {
        DEFAULT, INTERNATIONAL, US_PAPER, CUSTOM
    };
    Canvas *createCanvas(QString docName, double width, double height,
                          Canvas::DimensionUnit dimUnit, double resolution,
                          Canvas::ResolutionUnit resUnit) const;
    Ui::NewDialog *ui;
    int _resolution;
    Canvas::DimensionUnit _dimensionUnit;
    double getDoubleValue(QLineEdit *fieldVal);
    int getPixelValue(QLineEdit *field);
    void showZeroErrorMessage(QString fieldName);
    void checkDimensionValidity(double fieldVal);
    void displaySizeContents(NewDialog::PageSize size);
    QMap<Canvas::DimensionUnit, QString> dimensions;
    QMap<QString, PageSize> currPreset;
    QMap<DocType, QString> docTypes;

    QMap<QString, PageSize> getInternationalList();
    void initDimensionUnitList();
    void initPresetList();

};

#endif // NEWDIALOG_H
