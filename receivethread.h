#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include<QQueue>
#include <QMutex>
#include <QPainter>

#include "serialstruct.h"

class receiveThread
{
public:
    receiveThread();

    void pullSerialStruct();
    void readSerialStruct(command serialData);

protected:
    void checkParityBit(command serialData);
    void resend();

private:
    QMutex mutex;
    //QQueue<command> &serialQueue;
};

#endif // RECEIVETHREAD_H
