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

void Listener::processPendingDatagrams()
{
    cout << "socketti valmis, ehkä" << endl;
    do {
      QByteArray datagram;
      datagram.resize(udpSocket.pendingDatagramSize());
      QHostAddress sender;
      quint16 senderPort;

      udpSocket.readDatagram(datagram.data(), datagram.size(),
			      &sender, &senderPort);

      //processTheDatagram(datagram);
      
      XKeyEvent ev;
      ev.type = KeyPress;
      ev.display = QX11Info::display();
      ev.window = QX11Info::appRootWindow(); // ok, let's guess some values
      ev.root = QX11Info::appRootWindow();   // I don't know whether these have to be set
      ev.subwindow = None;       // to these values, but it seems to work, hmm
      ev.time = CurrentTime;
      ev.x = 0;
      ev.y = 0;
      ev.x_root = 0;
      ev.y_root = 0;
      ev.state = 0;
      ev.keycode = XStringToKeysym( '?' );
      if( ev.keycode == NoSymbol )
          return;
      ev.same_screen = true;
      XSendEvent( QX11Info::display(), InputFocus, false, 0, ( XEvent* )&ev );
      
    } while (udpSocket.hasPendingDatagrams());
}