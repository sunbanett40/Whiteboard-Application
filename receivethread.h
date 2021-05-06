#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QQueue>
#include <QMutex>
#include <QPainter>
#include <QImage>

#include "serialstruct.h"
#include "queue.h"

class receiveThread : public QObject
{
    Q_OBJECT


public:
    receiveThread();

    void pullSerialStruct();
    void readSerialStruct(QImage serialData);

public slots:
    void poll();

signals:
    void pulledFromQueue(QImage serialData);

protected:
    void checkParityBit(QImage serialData);
    void resend();

private:
    QMutex mutex;
    //queue *serialQueue;
};

#endif // RECEIVETHREAD_H
