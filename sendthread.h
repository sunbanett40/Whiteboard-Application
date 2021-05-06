#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QQueue>
#include <QMutex>
#include <QPainter>

#include "serialstruct.h"
#include "queue.h"

class sendThread : public QObject
{
    Q_OBJECT

public:
    sendThread(queue *sQueue);

public slots:
    void pushSerialStruct(QImage serialData);

protected:
    void setParityBit(command serialData);

private:
    QMutex mutex;
    queue *serialQueue;
};

#endif // SENDTHREAD_H
