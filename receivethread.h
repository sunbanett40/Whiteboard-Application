#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QQueue>
#include <QMutex>
#include <QPainter>

#include "serialstruct.h"

class receiveThread : public QObject
{
    Q_OBJECT


public:
    receiveThread();

    void pullSerialStruct();
    void readSerialStruct(command serialData);

public slots:
    void poll();

signals:
    void pulledSerialStruct(const command &serialData);

protected:
    void checkParityBit(command serialData);
    void resend();

private:
    QMutex mutex;
    //QQueue<command> &serialQueue;
};

#endif // RECEIVETHREAD_H
