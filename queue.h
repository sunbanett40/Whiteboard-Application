#ifndef QUEUE_H
#define QUEUE_H

#include <QQueue>
#include <QMutex>

template <class T>
class queue
{
public:
    explicit queue(int setupSize);

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

#endif // QUEUE_H
