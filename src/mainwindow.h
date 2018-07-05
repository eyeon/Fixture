#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QStandardPaths>

#include "dialogs/newdialog.h"
#include "widgets/paintwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createNewDocument(const Canvas *canvas);
    void updateLayers();

private slots:
    void updateWindow(QMdiSubWindow *window);

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionImport_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    const QString chooseFile();
    void addChildWindow(PaintWidget *widget, bool isNew);
    void addPaintWidget(PaintWidget *widget, bool isNew = false);
    PaintWidget *createPaintWidget(const QString &imagePath) const;
    bool isFileValid(const QString& fileName);
    bool isImageSupported(const QString& fileName);
    void rememberLastPath(const QString& fileName);
    QString _lastFileLoc;
};

#endif // MAINWINDOW_H
