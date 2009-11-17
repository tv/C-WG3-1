#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QInputDialog>
#include <QApplication>
#include "clientwindow.h"

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    MenuWidget(QWidget *parent, QStatusBar *statusBar);
    ~MenuWidget();
private:
public slots:
    void startGame(QString address);
    void askAddress();

signals:
    void showStatusMessage(QString msg, int timeout = 0);
    void enterGameState(QString address);
};

#endif // MENUWIDGET_H
