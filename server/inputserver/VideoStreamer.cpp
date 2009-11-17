#include "VideoStreamer.h"


using namespace std;

VideoStreamer::VideoStreamer(QObject* parent): QThread(parent)
{
    tcpServer = new QTcpServer(this);
}

VideoStreamer::~VideoStreamer()
{
    tcpServer->close();
}

void VideoStreamer::run()
{
    tcpServer->listen(QHostAddress::Any, 42803);
    
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(processIncomingTCP()));
}

void VideoStreamer::StartVideoOutput( quint32 ip )
{
    
    cout << "socketti2 valmis, ehkä" << endl;
    clientIP.setAddress(ip);
}

void VideoStreamer::processIncomingTCP()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    
    QByteArray block;
            
    //struct seomPacket *packet = getPacket(stream, type);
    
    do {
        QByteArray datagram;
        
        datagram = clientConnection->read(4096);

        if(!clientIP.isNull())
            outputSock.writeDatagram(datagram, clientIP, 13373);
        
    } while (clientConnection->isReadable());
}