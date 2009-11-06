#include "Listener.h"

using namespace std;

Listener::Listener(QObject* parent): QObject(parent)
{
    udpSocket.bind(45454);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

Listener::~Listener()
{
    udpSocket.close();
}

uint Listener::parseKeycode(QByteArray string)
{
    uint key = XStringToKeysym(string.trimmed().data());
    
    return key;
}

void Listener::processPendingDatagrams()
{
    do {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
    
        uint keycode = parseKeycode(datagram);
        
        cout << "tuli " << datagram.trimmed().data() << " - " << keycode << endl;
      
        XTestFakeKeyEvent( QX11Info::display(), keycode, true, CurrentTime );
      
        XTestFakeKeyEvent( QX11Info::display(), keycode, false, CurrentTime );
      
    } while (udpSocket.hasPendingDatagrams());
}