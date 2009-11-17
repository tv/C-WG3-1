#include "InputListener.h"

using namespace std;

InputListener::InputListener(QObject* parent): QObject(parent)
{
    cout << "socketti valmis, ehkä" << endl;
    udpSocket.bind(45455);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

InputListener::~InputListener()
{
    udpSocket.close();
}

quint32 InputListener::parseKeyCode(QByteArray string)
{
    cout << "ei toimi ei" << endl;
    QKeyEvent(QEvent::KeyPress, Qt::Key_F1, Qt::NoModifier);
    
    return eventti.nativeVirtualKey();
}

void InputListener::processPendingDatagrams()
{
    do {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        
        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        
        uint keycode = parseKeyCode(datagram);
        
        cout << "tuli " << datagram.trimmed().data() << " - " << keycode << endl;
      
        switch(datagram[0]){
            case KEYPRESS:
                XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), true, CurrentTime );
                break;
                
            case KEYRELEASE:
                XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case MOUSEX:
                XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case MOUSEY:
                XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case MOUSE1PRESS:
                XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case MOUSE1RELEASE:
                XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case MOUSE2PRESS:
                XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
                
            case MOUSE2RELEASE:
                XTestFakeKeyEvent( QX11Info::display(), parseKeyCode(datagram.right(1)), false, CurrentTime );
                break;
        
        }
        
        //
      
        //XTestFakeKeyEvent( QX11Info::display(), keycode, false, CurrentTime );
      
    } while (udpSocket.hasPendingDatagrams());
}