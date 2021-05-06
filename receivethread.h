#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QQueue>
#include <QMutex>
#include <QPainter>

#include "serialstruct.h"
#include "queue.h"

class receiveThread : public QObject
{
    Q_OBJECT


public:
    receiveThread(queue *sQueue);

    void pullSerialStruct();
    void readSerialStruct(command serialData);

public slots:
    void poll();

signals:
    //void pulledSerialStruct(const command &serialData);

protected:
    void checkParityBit(command serialData);
    void resend();

private:
    QMutex mutex;
    queue *serialQueue;
};

#endif // RECEIVETHREAD_H
