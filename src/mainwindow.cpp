#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools/tooloptions/transform_menu.h"

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
    bar->setElideMode(Qt::ElideLeft);

    setAcceptDrops(true);

    _lastFileLoc = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    initTools();
    initSignalsAndSlots();
    setDefaultTool(_transform);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSignalsAndSlots()
{
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
                     this, SLOT(updateWindow(QMdiSubWindow*)));

    connect(ui->mainToolBar,SIGNAL(actionTriggered(QAction*)),
            this,SLOT(changeTool(QAction*)));

    connect(ui->layerView,SIGNAL(itemSelectionChanged()),
             this,SLOT(onSelectionChange()));
}

void MainWindow::initTools()
{
    _toolsGroup = new QActionGroup(ui->mainToolBar);

    _transform = new Transform();
    _toolsGroup->addAction(_transform);
    _toolsList.push_back(_transform);

    _pan = new Pan();
    _toolsGroup->addAction(_pan);
    _toolsList.push_back(_pan);

    ui->mainToolBar->addActions(_toolsList);
}

void MainWindow::setDefaultTool(Tool *tool)
{
    tool->toggle();
    setCurrentTool(tool);
}

void MainWindow::setCurrentTool(Tool *tool)
{
    QWidget *menuWidget = tool->getToolMenu();

    if (_menu != NULL) {
        _menu->setVisible(false);
    }

    updateMenuFromCache(menuWidget);
    // TODO: Remember preferences
    _menu->setVisible(true);
    _currentTool = tool;
}

void MainWindow::updateMenuFromCache(QWidget *menuWidget)
{
    if (_toolMenuCache.contains(menuWidget)) {
        _menu = _toolMenuCache.value(menuWidget);
    }
    else {
        _menu = ui->toolMenuBar->addWidget(menuWidget);
        _toolMenuCache.insert(menuWidget, _menu);
    }
}
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();

        if (PaintWidget::isFileValid(fileName)) {
            rememberLastPath(fileName);
            addPaintWidget(new PaintWidget(fileName, _currentTool));
        }
    }
}

void MainWindow::addChildWindow(PaintWidget *widget,bool isNew)
{
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QMdiSubWindow *mdiSubWindow = ui->mdiArea->addSubWindow(widget);

    QString title;
    if (widget->getImagePath() != "") {
        QFileInfo info(widget->getImagePath());
        title = info.fileName() + "[*]";
    } else {
        title = "Untitled[*]";
    }

    mdiSubWindow->setWindowTitle(title);

    if (isNew) {
        mdiSubWindow->setWindowModified(true);
    }

    mdiSubWindow->installEventFilter(this);
    mdiSubWindow->show();
}

/**
 * @brief MainWindow::updateWindow
 * @param window
 */
void MainWindow::updateWindow(QMdiSubWindow *window)
{
    QString title = "Fixture";

    if (window != NULL) {
        title = window->windowTitle() + " - " + title;
        PaintWidget* wid = qobject_cast<PaintWidget*> (window->widget());
        ui->layerView->updateItems(wid->getItems());
    } else {
        ui->layerView->clear();
    }

    updateActions(window != NULL);
    setWindowTitle(title);
}

void MainWindow::updateActions(bool val)
{
    ui->actionImport->setEnabled(val);
    ui->actionSave->setEnabled(val);
    ui->actionSaveAs->setEnabled(val);
}

void MainWindow::changeTool(QAction *action)
{
    QMdiSubWindow *currentWindow = ui->mdiArea->activeSubWindow();
    setCurrentTool(dynamic_cast<Tool*>(action));

    if(currentWindow != NULL){
        PaintWidget* paintWidget = qobject_cast<PaintWidget*> (currentWindow->widget());
        paintWidget->setTool(_currentTool);

        if (_currentTool->getToolGroup() == Tool::PERCEPTION){
            //The cursor needs to be fixed for zoom here.
            paintWidget->setDragMode(QGraphicsView::ScrollHandDrag);
        }
        else {
            paintWidget->setDragMode(QGraphicsView::NoDrag);
        }
    }
}

void MainWindow::onSelectionChange()
{
    QMdiSubWindow *currentWindow = ui->mdiArea->activeSubWindow();

    if(currentWindow != NULL){
        QList<QListWidgetItem*> widgetSelectedItems = ui->layerView->selectedItems();
        QList<QListWidgetItem*> widgetItems = ui->layerView->getitems();
        QList<QListWidgetItem*>::iterator itr = widgetItems.begin();
        for(;itr != widgetItems.end();++itr){
            Layer *l = dynamic_cast<Layer*>(*itr);

            if(widgetSelectedItems.contains(*itr)){
                l->setSceneSelected(true);
            }else{
                l->setSceneSelected(false);
            }
        }
    }
}

void MainWindow::addPaintWidget(PaintWidget *widget,bool isNew)
{
    addChildWindow(widget,isNew);
    ui->mdiArea->setCursor(_currentTool->getToolCursor());
}

PaintWidget *MainWindow::createPaintWidget(const QString &imagePath) const
{
    return new PaintWidget(imagePath, _currentTool);
}

void MainWindow::on_actionOpen_triggered()
{
    const QString fileName = chooseFile();

    if (PaintWidget::isFileValid(fileName)) {
        rememberLastPath(fileName);
        addPaintWidget(new PaintWidget(fileName, _currentTool));
    }
}

void MainWindow::rememberLastPath(const QString &fileName)
{
    QFileInfo info(fileName);
    _lastFileLoc = info.absolutePath();
}

const QString MainWindow::chooseFile()
{

    return QFileDialog::getOpenFileName(this, tr("Open File"),
                _lastFileLoc,tr("Image Files (*.png *.jpg *.jpeg *.gif);;"
                                "PNG(*.png);;"
                                "JPEG(*.jpg *.jpeg);;"
                                "GIF(*.gif);;"
                                "TIFF(*.tif *.tiff);;"
                                "BMP(*.bmp);;"
                                "ICO(*.ico)"));
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionNew_triggered()
{
    NewDialog *newDialog = new NewDialog();
    connect(newDialog, SIGNAL(canvasAvailable(const Canvas*)), this, SLOT(createNewDocument(const Canvas*)));

    newDialog->show();
}

void MainWindow::createNewDocument(const Canvas *canvas)
{
    addPaintWidget(new PaintWidget(canvas, _currentTool), true);
    delete canvas;
}

void MainWindow::on_actionImport_triggered()
{
    const QString fileName = chooseFile();
    QMdiSubWindow *currentWindow = ui->mdiArea->activeSubWindow();
    PaintWidget* paintWidget = qobject_cast<PaintWidget*> (currentWindow->widget());

    paintWidget->importPathToLayer(fileName);
    ui->layerView->updateItems(paintWidget->getItems());
}

void MainWindow::on_actionSave_triggered()
{
}

void MainWindow::on_actionSaveAs_triggered()
{
    QMdiSubWindow *currentWindow = ui->mdiArea->activeSubWindow();
    PaintWidget* paintWidget = qobject_cast<PaintWidget*> (currentWindow->widget());

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                       _lastFileLoc,
                                       tr("Fixture Document (*.fxd *.fxt)"));

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << paintWidget->getItems().at(0);
}

QDataStream & operator << (QDataStream &stream, Layer *&layer)
{
    stream << layer->getName();
    qDebug() << layer->getName();
    return stream;
}
