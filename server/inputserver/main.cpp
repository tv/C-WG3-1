#include <QApplication>
#include <QPushButton>
#include <iostream>

using namespace std;
#include "InputListener.h"

int main(int argc, char *argv[])
{
    cout << "socketti valmis, ehkä" << endl;
    QApplication app(argc, argv);
    
    InputListener *inputListener = new InputListener();
    
    inputListener->run();
    
    return app.exec();
}