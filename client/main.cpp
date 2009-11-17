#include <QtGui/QApplication>
#include "clientwindow.h"
#include "VLCWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWindow w;
    w.resize(800,600);
    w.show();

    return a.exec();
}
