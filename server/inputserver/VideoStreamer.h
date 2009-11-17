#ifndef VIDEOSTREAMER_H
#define VIDEOSTREAMER_H


#include <QtNetwork>
#include <QUdpSocket>
#include <QHostAddress>
#include <iostream>

// #include <seom/seom.h>

class VideoStreamer: public QThread
{
    Q_OBJECT
    public:
        virtual void run();
        
        VideoStreamer(QObject * parent = 0);
        ~VideoStreamer();
        
        bool videoStreamStarted;
    private slots:
        void processIncomingTCP();
        
    private:
        QTcpServer * tcpServer;
        QUdpSocket outputSock;
        QHostAddress clientIP;
        
    public slots:
        void StartVideoOutput(quint32 ip); 
};

#endif // VIDEOSTREAMER_H
