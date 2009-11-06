#include "clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //iStatusBar = new QStatusBar(this);
    //iStatusBar->showMessage("PERHANAAAAAAAAAAAAAAAAAAAAAAAAAAA", 5000);
    //this->grabKeyboard();
    //this->grabMouse();


    //this->player = 0;
    //this->player = new VLCWidget(this);
    //this->player->resize(640,480);
    //this->player->playFile("E:\\Documents\\Kurssit\\MMJ\\Qt_client\\Client\\debug\\test.avi");

    //statusBar()->showMessage("Wellcome!", 2000);

    //statusBar()->showMessage("Hello", 500);
    //MenuWidget* menu = new MenuWidget(this, statusBar());
    //setCentralWidget(menu);
    enterMenuState();

}

ClientWindow::~ClientWindow()
{

}

void ClientWindow::enterGameState( QString address )
{
    iState = ClientWindow::GAMESTATE;
    statusBar()->showMessage("Entering game state...", 500);
    VLCWidget* vlc = new VLCWidget(address, statusBar(), this);
    setCentralWidget(vlc);
    grabKeyboard();
}

void ClientWindow::enterMenuState()
{
    iState = ClientWindow::MENUSTATE;
    releaseKeyboard();
    statusBar()->showMessage("Entering menu state...", 500);
    MenuWidget* menu = new MenuWidget(this, statusBar());
    menu->setFocus();
    setCentralWidget(menu);
}

void ClientWindow::keyPressEvent( QKeyEvent *e )
{
    switch( e->key() )
    {
        case Qt::Key_Left:
            //this->label->setText("VASEN");
            //if( this->player == 0 )
            //    this->player = new VLCWidget("E:\\Documents\\Kurssit\\MMJ\\Qt_client\\Client\\debug\\test.avi", this);
            break;
        case Qt::Key_Down:
            statusBar()->showMessage("DOWN");
            break;
        case Qt::Key_Up:
            statusBar()->showMessage("UP");
            break;
        case Qt::Key_F1:
            enterMenuState();
    }
}
