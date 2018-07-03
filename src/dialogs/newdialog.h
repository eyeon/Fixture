#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include "../model/canvas.h"
#include "../mainwindow.h"
#include <QDialog>
#include <QLineEdit>

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

private:
    Canvas *createDocument(QString docName, double width, double height,
                          Canvas::DimensionUnit dimUnit, double resolution,
                          Canvas::ResolutionUnit resUnit) const;
    Ui::NewDialog *ui;
    int getIntValue(QLineEdit *field);
    void showZeroErrorMessage(QString fieldName);
    void checkDimensionValidity(int fieldVal);

};

#endif // NEWDIALOG_H
