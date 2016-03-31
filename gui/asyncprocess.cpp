#include "asyncprocess.h"

#include <QStringList>


void AsyncProcess::start(QString program, QString arguments)
{
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()));
    process->start(program, QStringList(arguments));
}

void AsyncProcess::readStandardOutput()
{
    QByteArray processOutput;
    processOutput = process->readAllStandardOutput();

    qDebug() << "AsyncProcess: " << QString(processOutput);
}