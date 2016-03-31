#ifndef ASYNCPROCESS_H
#define ASYNCPROCESS_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QString>


class AsyncProcess : public QObject
{
    Q_OBJECT
public:
    AsyncProcess() : QObject() {};
    void start(QString program, QString arguments);
private slots:
    void readStandardOutput();
private:
    QProcess *process;
};

#endif // ASYNCPROCESS_H