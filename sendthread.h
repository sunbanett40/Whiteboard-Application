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
    sendThread(queue<command> *sQueue);

    command setSerialStruct(uint8_t op, QPoint pos);
    command setSerialStruct(uint8_t op, int penWidth, QColor penColour);

public slots:
    void pushSerialStruct(command serialData);

protected:
    void setParityBit(command serialData);

private:
    QMutex mutex;
    queue<command> *serialQueue;
};

#endif // SENDTHREAD_H
