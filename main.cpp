#include "mainwindow.h"
#include <QApplication>
#include "QList"

int main(int argc, char *argv[])
{
    qRegisterMetaType <QStringList>("QStringList");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
