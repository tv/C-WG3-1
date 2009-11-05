#include <QtNetwork>
#include <QObject>
#include <QUdpSocket>
#include <QKeyEvent>
#include <QHostAddress>
#include <X11/Xlib.h>
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
 private:
   QUdpSocket udpSocket;
};