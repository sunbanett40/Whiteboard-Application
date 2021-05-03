#include <QDebug>

#include "queue.h"


template <class T>
queue<T>::queue(int setupSize)
{
    currentSize=0;
    maxSize = setupSize;

    //Open queue
    isOpen = true;
}


template <class T>
void queue<T>::pushToQueue(T const &pushedItem)
{
    // Create temporary item to store pushed item
    T tempItem;
    tempItem = pushedItem;

    // Lock the thread so queue can't be modified by other threads
    mutex.lock();

    // Wait until there is space in the queue
    while (currentSize == maxSize)
    {
        this->usleep(1);
    }

    // Check that the queue is not closed
    if (isOpen == false)
    {
        qDebug() << "Trying to push to a closed queue.";
    }

    // Push to queue.
    serialisedQueue.enqueue(tempItem);
    currentSize++;

    this->usleep(10);
    // Unlock thread so queue can be accessed again
    mutex.unlock();
}



template <class T>
bool queue<T>::pullFromQueue(T &pulledItem)
{
    // Create temporary queue to store items
    QQueue<T> tempQueue;

    // Lock the thread so queue can't be modified by other threads
    mutex.lock();

    // If the queue is empty and closed we cannot return anything
    if ((serialisedQueue.head() == nullptr) && (isOpen == false))
    {
        //No item to retrieve
        return false;
    }

    // If there is no item then we wait until there is one
    while ((serialisedQueue.head() == nullptr) && (isOpen == true))
    {
        this->msleep(1);
    }

    // Get item from threadsafe queue and write the value
    currentSize--;
    pulledItem = serialisedQueue.dequeue();

    // Unlock thread so queue can be accessed again
    mutex.unlock();

    //Item retrieved successfully
    return true;
}
