#ifndef THREADHANDLER_H
#define THREADHANDLER_H

#include <QThread>
#include <QProcess>
#include <iostream>

class ThreadHandler : public QThread
{
    Q_OBJECT
public:
    ThreadHandler(QObject *parent);
    void run();
    QProcess * process;
    QProcess::ProcessState state();
public slots:
    void runProcess(QString path);
private:
    QString path;
private slots:
    void readProcessOut();
};

#endif // THREADHANDLER_H
