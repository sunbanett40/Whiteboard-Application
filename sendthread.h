#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QQueue>
#include <QMutex>
#include <QPainter>

#include "drawinformation.h"
#include "queue.h"

class sendThread : public QObject
{
    Q_OBJECT

public:
    sendThread();

public slots:
    void pushSerialStruct(drawInfoPosition serialData);
    void pushSerialStruct(drawInfoPen serialData);

protected:
    void setParityBit(drawInfoPosition serialData);
    void setParityBit(drawInfoPen serialData);

private:
    QMutex mutex;
    //queue *serialQueue;
};

#endif // SENDTHREAD_H
