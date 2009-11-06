#include <QApplication>
#include <QPushButton>
#include <iostream>
using namespace std;
#include "Listener.h"

int main(int argc, char *argv[])
{
    cout << "socketti valmis, ehkä" << endl;
    QApplication app(argc, argv);
    
    Listener sock;
    return app.exec();
}