#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QMutex>
#include <QPainter>

#include "serialstruct.h"

class sendThread
{
public:
    sendThread();

    command setSerialStruct(uint8_t op, QPoint pos);
    command setSerialStruct(uint8_t op, int penWidth, QColor penColour);

    void sendSerialStruct(command serialData);

protected:
    void setParityBit(command serialData);

private:
    QMutex mutex;
};

#endif // SENDTHREAD_H