<<<<<<< HEAD
#include <QtGui/QApplication>
#include "clientwindow.h"
#include "VLCWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWindow w;
    w.resize(800,600);
    w.show();

    /*
    VLCWidget player;
    player.resize(640,480);
    player.playFile("E:\\Documents\\Kurssit\\MMJ\\Qt_client\\Client\\debug\\test.avi");
    player.show();
    */

    return a.exec();
}
=======
#include <QtGui/QApplication>
#include "clientwindow.h"
#include "VLCWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWindow w;
    w.resize(960,600);
    w.show();

    /*
    VLCWidget player;
    player.resize(640,480);
    player.playFile("E:\\Documents\\Kurssit\\MMJ\\Qt_client\\Client\\debug\\test.avi");
    player.show();
    */

    return a.exec();
}
>>>>>>> fe89c063332f1b72eccb2883116337156ce72c05
