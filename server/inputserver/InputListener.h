#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H


#include <QtNetwork>
#include <QObject>
#include <QUdpSocket>
#include <QKeyEvent>
#include <QHostAddress>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <QX11Info>
#include <iostream>

#include "VideoStreamer.h"

#include <qthread.h>


class InputListener: public QThread
{
    Q_OBJECT
    public:
        virtual void run();
        InputListener(QObject * parent = 0);
        ~InputListener();
    private slots:
        void processPendingDatagrams();
        uint parseKeycode(QByteArray string);
    private:
        QUdpSocket *udpSocket;
        VideoStreamer videoStream;
        bool    videoStreamStarted;
    signals:
        void startVideoStream(quint32 ip);

};

#endif // INPUTLISTENER_H