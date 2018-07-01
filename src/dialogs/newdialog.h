#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include "../model/document.h"
#include "../mainwindow.h"
#include <QDialog>

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
    void documentAvailable(const Document *document);

private slots:
    void on_actionOk_clicked();
    void on_actionCancel_clicked();

private:
    Document *createDocument(QString docName, double width, double height,
                          Document::DimensionUnit dimUnit, double resolution,
                          Document::ResolutionUnit resUnit) const;
    Ui::NewDialog *ui;
};

#endif // NEWDIALOG_H
