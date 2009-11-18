#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <QtGui>
#include <QtNetwork>
#include <QObject>
#include <QUdpSocket>
#include <QKeyEvent>
#include <QEvent>
#include <QHostAddress>
#include <QByteArray>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <QX11Info>
#include <iostream>

class InputListener: public QObject
{
    Q_OBJECT
    
    static const char KEYPRESS =       0x00;
    static const char KEYRELEASE =     0x01;
    static const char MOUSEX =         0x02;
    static const char MOUSEY =         0x03;
    static const char MOUSE1PRESS =    0x04;
    static const char MOUSE1RELEASE =  0x05;
    static const char MOUSE2PRESS =    0x06;
    static const char MOUSE2RELEASE =  0x07;
    public:
        InputListener(QObject * parent = 0);
        ~InputListener();
        
    private slots:
        
        void processPendingDatagrams();
        
    private:
        quint32 parseKeycode(QByteArray string);
		uint InputListener::handle_qkey(QKeyEvent *event);
        QUdpSocket *udpSocket;
        
};

#endif // INPUTLISTENER_H
