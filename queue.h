#ifndef QUEUE_H
#define QUEUE_H

#include <QQueue>

template <typename  T>
class queue
{
public:
    explicit queue(int maxSize);

    void pushToQueue(T const &pushedItem);
    void pullFromQueue(T &pushedItem);

private:
    int currentSize;
    int maxSize;

    //queue of data packets
    QQueue<T> serialisedQueue;

};

#endif // QUEUE_H
