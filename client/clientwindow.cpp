#include "clientwindow.h"

#define INPUTSERVERPORT 45455

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
{
    iUdpSocket = new QUdpSocket(this);
    iServerAddress = QHostAddress();
    enterMenuState();

}

ClientWindow::~ClientWindow()
{

}

void ClientWindow::enterGameState( QString address )
{

    iState = ClientWindow::GAMESTATE;
    statusBar()->showMessage("Entering game state...", 500);

    iServerAddress.setAddress(address);
    iUdpSocket->writeDatagram( "start server", iServerAddress, INPUTSERVERPORT );

    QString line;
    QFile file;
    file.setFileName("stream.sdp");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write("v=0\n");
    line = QString("o=- 0 0 IN IP4 ") + address + QString("\n");
    file.write(line.toAscii());
    file.write("s=No Name\n");
    line = QString("c=IN IP4 ") + address + QString("\n");
    file.write(line.toAscii());
    file.write("t=0 0\n");
    file.write("a=tool:libavformat 52.39.2\n");
    file.write("m=video 45456 RTP/AVP 96\n");
    file.write("b=AS:200\n");
    file.write("a=rtpmap:96 H263-2000/90000\n");
    file.close();

    QString path = QString("stream.sdp");
    //sleep(4);
    VLCWidget* vlc = new VLCWidget(path, statusBar(), this);

    setCentralWidget(vlc);
    
    //showFullScreen();
    //grabMouse();
    grabKeyboard();
    setMouseTracking(true);

    QCursor cursor = QCursor(Qt::BlankCursor);
    setCursor(cursor);
}

void ClientWindow::enterMenuState()
{
    iState = ClientWindow::MENUSTATE;
    releaseKeyboard();
    //releaseMouse();
    setMouseTracking(false);
    QCursor cursor = QCursor();
    setCursor(cursor);
    statusBar()->showMessage("Entering menu state...", 500);
    MenuWidget* menu = new MenuWidget(this, statusBar());
    menu->setFocus();
    setCentralWidget(menu);
}

void ClientWindow::mouseMoveEvent( QMouseEvent *e )
{
    if ( iState == ClientWindow::MENUSTATE )
        return;

    QPoint pos = e->pos();
    QPoint c = QPoint(width(), height());
    c /= 2;
    QCursor::setPos(mapToGlobal(c));
    QPoint delta = pos - c;

    statusBar()->showMessage("Mouse moving...", 100);
    //int x = e->globalX();
    //int y = e->globalY();
    //int deltaX = x-iMouseX;
    //int deltaY = y-iMouseY;
    //iMouseX = x;
    //iMouseY = y;

    QByteArray data = QByteArray(1, ClientWindow::MOUSEX);
    data.append(QByteArray::number(delta.x()));
    iUdpSocket->writeDatagram( data, iServerAddress, INPUTSERVERPORT );

    data = QByteArray(1, ClientWindow::MOUSEY);
    data.append(QByteArray::number(delta.y()));
    iUdpSocket->writeDatagram( data, iServerAddress, INPUTSERVERPORT );
}

void ClientWindow::mousePressEvent( QMouseEvent *e )
{
    if ( iState == ClientWindow::MENUSTATE )
        return;
    QByteArray data;
    if ( e->button() == Qt::LeftButton )
        data = QByteArray(1, ClientWindow::MOUSE1PRESS);
    else if ( e->button() == Qt::RightButton )
        data = QByteArray(1, ClientWindow::MOUSE2PRESS);
    else
        return;
    iUdpSocket->writeDatagram( data, iServerAddress, INPUTSERVERPORT );

}

void ClientWindow::mouseReleaseEvent( QMouseEvent *e )
{
    if ( iState == ClientWindow::MENUSTATE )
        return;
    QByteArray data;
    if ( e->button() == Qt::LeftButton )
        data = QByteArray(1, ClientWindow::MOUSE1RELEASE);
    else if ( e->button() == Qt::RightButton )
        data = QByteArray(1, ClientWindow::MOUSE2RELEASE);
    else
        return;
    iUdpSocket->writeDatagram( data, iServerAddress, INPUTSERVERPORT );

}

void ClientWindow::keyPressEvent( QKeyEvent *e )
{
    if ( iState == ClientWindow::MENUSTATE )
        return;

    switch( e->key() )
    {
        case Qt::Key_F1:
            enterMenuState();
            break;
        default:
            //statusBar()->showMessage(QString::number(e->key()), 5000);
            QByteArray data = QByteArray(1, ClientWindow::KEYPRESS);
            data.append(QByteArray::number(e->key()));
            iUdpSocket->writeDatagram ( data,  iServerAddress, INPUTSERVERPORT );
            break;
    }
}

void ClientWindow::keyReleaseEvent( QKeyEvent *e )
{
    if ( iState == ClientWindow::MENUSTATE )
        return;

    switch( e->key() )
    {
        case Qt::Key_F1:
            //enterMenuState();
            break;
        default:
            //statusBar()->showMessage(QString::number(e->key()), 5000);
            QByteArray data = QByteArray(1, ClientWindow::KEYRELEASE);
            data.append(QByteArray::number(e->key()));
            iUdpSocket->writeDatagram ( data,  iServerAddress, INPUTSERVERPORT );
            break;
    }
}
