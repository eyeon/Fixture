#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.showMaximized();
    w.show();

    QFile styleFile(":/styles/basic.qss");
    styleFile.open(QFile::ReadOnly);

    QString style(styleFile.readAll() );
    w.setStyleSheet(style);

    return a.exec();
}
