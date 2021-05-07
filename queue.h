/*
Project:    Whiteboard Chat Application - P20 Qt Project
Author:     Joseph Butterworth
License:    This work is licensed under the Creative Commons Attribution-ShareAlike License.
            View this license at https://creativecommons.org/licenses/

I tried to implement a thread safe queue template class
Went through a lot of revisions
Whenever it was called it created a SIGSEGV error
Literally impossible to debug
Am running out of time
Implementing a class that both threads have access to with signals and slots
Hope this works
I hate Qt
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <QQueue>
#include <QMutex>
#include <QImage>

#include "serialstruct.h"
#include "drawinformation.h"
/*
class queue
{
    Q_OBJECT

public:
    queue(int setupSize);
    ~queue() = default;

signals:
    //void pullFromQueue(QImage);
    //void pullFromQueue(bool[40]);

public slots:
    //void pushToQueue(QImage);
    //void pushToQueue(bool[40]);

    //void pullFromQueueRequest();

private:

    // Controls queue size
    int currentSize;
    int maxSize;

    // Is the queue open?
    bool isOpen;

    //QMutex mutex;

    // Queue of data packets
    //QQueue<QImage> imageQueue;
    //QQueue<bool[40]> serialisedQueue;
};

template <class T>
class queue
{
public:
    queue(int setupSize);

    void pushToQueue(T const &pushedItem);
    bool pullFromQueue(T &pulledItem);

private:
    // Controls queue size
    int currentSize;
    int maxSize;

    // Is the queue open?
    bool isOpen;

    QMutex mutex;

    // Queue of data packets
    QQueue<T> serialisedQueue;

};

template class queue<command>;
*/

#endif // QUEUE_H
