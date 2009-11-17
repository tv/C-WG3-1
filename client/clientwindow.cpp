#include "clientwindow.h"

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
    //VLCWidget* vlc = new VLCWidget(address, statusBar(), this);
    iServerAddress.setAddress("10.117.0.49");
    //statusBar()->showMessage(iServerAddress.toString(), 2000);
    VLCWidget* vlc = new VLCWidget("E:\\Documents\\Kurssit\\MMJ\\Qt_client\\Client\\debug\\test.avi", statusBar(), this);
    setCentralWidget(vlc);
    //showFullScreen();
    grabKeyboard();
    grabMouse();
    setMouseTracking(true);
}

void ClientWindow::enterMenuState()
{
    iState = ClientWindow::MENUSTATE;
    releaseKeyboard();
    releaseMouse();
    setMouseTracking(false);
    statusBar()->showMessage("Entering menu state...", 500);
    MenuWidget* menu = new MenuWidget(this, statusBar());
    menu->setFocus();
    setCentralWidget(menu);
}

void ClientWindow::mouseMoveEvent( QMouseEvent *e )
{
    //statusBar()->showMessage("Mouse...", 100);
    int x = e->globalX();
    int y = e->globalY();
    int deltaX = x-iMouseX;
    int deltaY = y-iMouseY;
    iMouseX = x;
    iMouseY = y;

    QByteArray data = QByteArray(1, ClientWindow::MOUSEX);
    data.append(QByteArray::number(deltaX));
    iUdpSocket->writeDatagram( data, iServerAddress, 1111 );

    data = QByteArray(1, ClientWindow::MOUSEY);
    data.append(QByteArray::number(deltaY));
    iUdpSocket->writeDatagram( data, iServerAddress, 1111 );

    //statusBar()->showMessage(data, 10000);

}

void ClientWindow::mousePressEvent( QMouseEvent *e )
{
    QByteArray data;
    if ( e->button() == Qt::LeftButton )
        data = QByteArray(1, ClientWindow::MOUSE1PRESS);
    else if ( e->button() == Qt::RightButton )
        data = QByteArray(1, ClientWindow::MOUSE2PRESS);
    else
        return;
    iUdpSocket->writeDatagram( data, iServerAddress, 1111 );

}

void ClientWindow::mouseReleaseEvent( QMouseEvent *e )
{
    QByteArray data;
    if ( e->button() == Qt::LeftButton )
        data = QByteArray(1, ClientWindow::MOUSE1RELEASE);
    else if ( e->button() == Qt::RightButton )
        data = QByteArray(1, ClientWindow::MOUSE2RELEASE);
    else
        return;
    iUdpSocket->writeDatagram( data, iServerAddress, 1111 );

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
            iUdpSocket->writeDatagram ( data,  iServerAddress, 11111 );
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
            iUdpSocket->writeDatagram ( data,  iServerAddress, 11111 );
            break;
    }
}
