#include <QApplication>
#include <QPushButton>
#include <iostream>
using namespace std;
#include "Listener.h"

int main(int argc, char *argv[])
{
    cout << "socketti valmis, ehkä" << endl;
    QApplication app(argc, argv);
    
    QKeyEvent button = QKeyEvent(QEvent::KeyPress, Qt::Key_Question, Qt::NoModifier);
    QApplication::sendEvent(&app, &button);
    
    Listener sock;
    return app.exec();
}