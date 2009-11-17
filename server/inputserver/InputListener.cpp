#include "InputListener.h"

using namespace std;

InputListener::InputListener(QObject* parent): QThread(parent)
{
    videoStreamStarted = false;
}

InputListener::~InputListener()
{
    udpSocket->close();
}

void InputListener::run()
{
    udpSocket = new QUdpSocket();
    qDebug("Binding InputListener to port 45454");
    udpSocket->bind(45454);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    qDebug("connect to datagram process completed");
}
uint InputListener::parseKeycode(QByteArray string)
{
    uint key = XStringToKeysym(string.trimmed().data());
    
    return key;
}

void InputListener::processPendingDatagrams()
{
    qDebug("Incoming Datagrams");
    do {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        
        qDebug("Reading data");

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        
        if(!videoStreamStarted)
        {
            qDebug("Trying to emit videostreamer to ip: ", sender);
            emit(startVideoStream(sender.toIPv4Address()));
            videoStreamStarted = true;
        }
    
        uint keycode = parseKeycode(datagram);
        
        cout << "tuli " << datagram.trimmed().data() << " - " << keycode << endl;
      
        //XTestFakeKeyEvent( QX11Info::display(), keycode, true, CurrentTime );
      
        //XTestFakeKeyEvent( QX11Info::display(), keycode, false, CurrentTime );
      
    } while (udpSocket->hasPendingDatagrams());
}