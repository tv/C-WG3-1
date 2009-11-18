#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QWidget>
#include <QStatusBar>
#include <QPalette>
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include "VLCWidget.h"
#include "menuwidget.h"

#define MENU_WIDTH 200
#define MENU_HEIGHT 400

class ClientWindow : public QMainWindow
{
    Q_OBJECT
    enum State {GAMESTATE, MENUSTATE};
    static const char KEYPRESS =       0x00;
    static const char KEYRELEASE =     0x01;
    static const char MOUSEX =         0x02;
    static const char MOUSEY =         0x03;
    static const char MOUSE1PRESS =    0x04;
    static const char MOUSE1RELEASE =  0x05;
    static const char MOUSE2PRESS =    0x06;
    static const char MOUSE2RELEASE =  0x07;
public:
    ClientWindow(QWidget *parent = 0);
    ~ClientWindow();

private:

    int iState;
    QUdpSocket * iUdpSocket;
    QHostAddress iServerAddress;
    int iMouseX;
    int iMouseY;

protected:
    void keyPressEvent( QKeyEvent *e );
    void keyReleaseEvent( QKeyEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void mousePressEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e);


public slots:
    void enterGameState( QString address );
    void enterMenuState();
};

#endif // CLIENTWINDOW_H
