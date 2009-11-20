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

    //statusBar()->showMessage(iServerAddress.toString(), 2000);
    iServerAddress.setAddress(address);
    iUdpSocket->writeDatagram( "start server", iServerAddress, INPUTSERVERPORT );
    //VLCWidget* vlc = new VLCWidget("/home/tv/Desktop/Californication.S03E08.720p.HDTV.X264-DIMENSION.mkv", statusBar(), this);
    //VLCWidget* vlc = new VLCWidget("E:\\Documents\\Kurssit\\MMJ\\Qt_client\\Client\\debug\\test.avi", statusBar(), this);
    QString path = QString("http://");
    path.append(iServerAddress.toString());
    path.append(":3022/localhost/stream");
    //sleep(4);
    VLCWidget* vlc = new VLCWidget(path, statusBar(), this);

    setCentralWidget(vlc);
    //showFullScreen();
    grabKeyboard();
    //grabMouse();
    setMouseTracking(true);

    QCursor cursor = QCursor(Qt::BlankCursor);
    //setCursor(cursor);
}

void ClientWindow::enterMenuState()
{
    iState = ClientWindow::MENUSTATE;
    releaseKeyboard();
    //releaseMouse();
    setMouseTracking(false);
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
