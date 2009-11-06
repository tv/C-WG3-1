#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QWidget>
#include <QStatusBar>
#include <QPalette>
#include "VLCWidget.h"
#include "menuwidget.h"

#define MENU_WIDTH 200
#define MENU_HEIGHT 400

class ClientWindow : public QMainWindow
{
    Q_OBJECT
    enum State {GAMESTATE, MENUSTATE};
public:
    ClientWindow(QWidget *parent = 0);
    ~ClientWindow();

private:

    int iState;
    //QLabel *iLabel;
    //VLCWidget *iPlayer;
    //QWidget *iContent;
    //QStatusBar *iStatusBar;

protected:
    void keyPressEvent( QKeyEvent *e );

public slots:
    void enterGameState( QString address );
    void enterMenuState();
};

#endif // CLIENTWINDOW_H
