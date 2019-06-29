#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Fixture::MainWindow w(nullptr);
    w.show();
    return QApplication::exec();
}
