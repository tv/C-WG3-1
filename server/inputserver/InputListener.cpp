#include "InputListener.h"

using namespace std;

InputListener::InputListener(QObject* parent): QThread(parent)
{
}

InputListener::~InputListener()
{
    udpSocket->close();
}

void InputListener::run()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(45454);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
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
        
        uint keycode = parseKeycode(datagram);
        
        cout << "tuli " << datagram.trimmed().data() << " - " << keycode << endl;
      
        //XTestFakeKeyEvent( QX11Info::display(), keycode, true, CurrentTime );
      
        //XTestFakeKeyEvent( QX11Info::display(), keycode, false, CurrentTime );
      
    } while (udpSocket->hasPendingDatagrams());
}