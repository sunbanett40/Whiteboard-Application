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
    void readSerialStruct(drawInfoPosition serialData);

public slots:
    void poll();

signals:
    void pulledFromQueue(drawInfoPosition serialData);

protected:
    void checkParityBit(drawInfoPosition serialData);
    void resend();

private:
    QMutex mutex;
    //queue *serialQueue;
};

#endif // RECEIVETHREAD_H
