#ifndef QUEUE_H
#define QUEUE_H

#include <QQueue>

template <class T>
class queue
{
public:
    explicit queue(int setupSize)
    {
    currentSize=0;
    maxSize = setupSize;
    }

    void pushToQueue(T const &pushedItem);
    void pullFromQueue(T &pushedItem);

private:
    int currentSize;
    int maxSize;

    //queue of data packets
    QQueue<T> serialisedQueue;

};

#endif // QUEUE_H
