#include "ThreadHandler.h"

ThreadHandler::ThreadHandler(QObject* parent): QThread(parent)
{
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readProcessOut()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readProcessOut()));
}

void ThreadHandler::run()
{
    if(!path.isEmpty())
        process->execute(path);

}

void ThreadHandler::runProcess(QString pat)
{
    path = QString(pat);

    start();
}

QProcess::ProcessState ThreadHandler::state()
{
    return process->state();
}

void ThreadHandler::readProcessOut()
{
    std::cout << process->readAllStandardError().data() << std::endl;
    std::cout << process->readAllStandardOutput().data() << std::endl;
}
