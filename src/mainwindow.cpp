#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    ui->mdiArea->setTabsClosable(true);
    ui->mdiArea->setTabsMovable(true);
    QTabBar *bar=ui->mdiArea->findChild<QTabBar*>();
    bar->setExpanding(false);
    bar->setDrawBase(false);
    QObject::connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateWindowTitle(QMdiSubWindow*)));

    _lastFileLoc = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addChildWindow(PaintWidget *widget)
{
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QMdiSubWindow *mdiSubWindow = ui->mdiArea->addSubWindow(widget);
    QString title = widget->getImagePath().isEmpty() ? "Untitled" : widget->getImagePath();
    title = title + " [*]";
    mdiSubWindow->setWindowTitle(title);

    mdiSubWindow->installEventFilter(this);
    mdiSubWindow->show();
}
/**
 * @brief MainWindow::updateWindowTitle
 * Updates window title to focused window
 * @param window
 */
void MainWindow::updateWindowTitle(QMdiSubWindow *window)
{
    QString title = "Fixture";

    if (window != NULL) {
        title = window->windowTitle() + " - " + title;
    }
    setWindowTitle(title);
}

void MainWindow::addPaintWidget(PaintWidget *widget)
{
    addChildWindow(widget);
}

PaintWidget *MainWindow::createPaintWidget(const QString &imagePath) const
{
    return new PaintWidget(imagePath);
}

void MainWindow::on_actionOpen_triggered()
{
    const QString& fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                _lastFileLoc,tr("Image Files (*.png *.jpg *.jpeg *.gif);;"
                                "PNG(*.png);;"
                                "JPEG(*.jpg *.jpeg);;"
                                "GIF(*.gif);;"
                                "TIFF(*.tif *.tiff);;"
                                "BMP(*.bmp);;"
                                "ICO(*.ico)"));

    if (isFileValid(fileName)) {
        QFileInfo info(fileName);
        _lastFileLoc = info.absolutePath();
        addPaintWidget(new PaintWidget(fileName));
    }
}

bool MainWindow::isFileValid(const QString& fileName)
{
    return isImageSupported(fileName);
}

bool MainWindow::isImageSupported(const QString &fileName)
{
    QImageReader reader(fileName);
    return reader.format() != "";
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionNew_triggered()
{
    NewDialog *newDialog = new NewDialog();
    QObject::connect(newDialog, SIGNAL(canvasAvailable(const Canvas*)), this, SLOT(createNewDocument(const Canvas*)));

    newDialog->show();
}

void MainWindow::createNewDocument(const Canvas *canvas)
{
    addPaintWidget(new PaintWidget(canvas));
    delete canvas;
}
