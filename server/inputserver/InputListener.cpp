#include "InputListener.h"

using namespace std;

InputListener::InputListener(QObject* parent): QObject(parent)
{
    cout << "socketti valmis, ehkä" << endl;
    udpSocket = new QUdpSocket();
    if(udpSocket->bind(45455) != -1)
        cout << "bindaus onnistui" << endl;

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

InputListener::~InputListener()
{
    udpSocket->close();
}

quint32 InputListener::parseKeycode(QByteArray string)
{

    QKeyEvent eventti = QKeyEvent((QEvent::Type)6, string.toInt(), Qt::NoModifier);

    return eventti.nativeVirtualKey();
}

void InputListener::processPendingDatagrams()
{
    cout << "pending datagrams" << endl;
    do {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        quint32 keycode;
        
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        switch(datagram[0]){
            case InputListener::KEYPRESS:
                keycode = parseKeycode(datagram.right(datagram.size()-1));
                cout << "tuli " << datagram.right(datagram.size()-1).toInt() << " - " << keycode << endl;
                XTestFakeKeyEvent( QX11Info::display(), keycode, true, CurrentTime );
                break;
                
            case InputListener::KEYRELEASE:
                XTestFakeKeyEvent( QX11Info::display(), parseKeycode(datagram.right(1)), false, CurrentTime );
                break;
                
            case InputListener::MOUSEX:
                //XTestFakeKeyEvent( QX11Info::display(), parseKeycode(datagram.right(1)), false, CurrentTime );
                break;
                
            case InputListener::MOUSEY:
                //XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case InputListener::MOUSE1PRESS:
                //XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case InputListener::MOUSE1RELEASE:
                //XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case InputListener::MOUSE2PRESS:
                //XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case InputListener::MOUSE2RELEASE:
                //XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
        
        }
        
        //
      
        //XTestFakeKeyEvent( QX11Info::display(), keycode, false, CurrentTime );
      
    } while (udpSocket->hasPendingDatagrams());
}
