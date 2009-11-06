

#include <QtNetwork>
#include <QObject>
#include <QUdpSocket>
#include <QKeyEvent>
#include <QHostAddress>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <QX11Info>
#include <iostream>



class Listener: public QObject
{
Q_OBJECT
public:
    Listener(QObject * parent = 0);
    ~Listener();
private slots:
    void processPendingDatagrams();
    uint parseKeycode(QByteArray string);
private:
    QUdpSocket udpSocket;
};