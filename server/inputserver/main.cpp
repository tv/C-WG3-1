#include <QApplication>
#include <QPushButton>
#include <iostream>

using namespace std;
#include "InputListener.h"

int main(int argc, char *argv[])
{
    
    QApplication app(argc, argv);
    
    InputListener inputListener;
    
    
    return app.exec();
}