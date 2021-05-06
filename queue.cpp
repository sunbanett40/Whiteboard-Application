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

#include <QDebug>

#include "queue.h"

queue::queue(int setupSize)
{
    currentSize=0;
    maxSize = setupSize;

    //Open queue
    isOpen = true;
}

void queue::pushToQueue(QImage pushedItem)
{
    // Create temporary item to store pushed item
    QImage tempItem;
    tempItem = pushedItem;

    // Lock the thread so queue can't be modified by other threads
    mutex.lock();

    // Wait until there is space in the queue
    while (currentSize == maxSize)
    {}

    // Check that the queue is not closed
    if (isOpen == false)
    {
        qDebug() << "Trying to push to a closed queue.";
    }

    // Push to queue.
    imageQueue.enqueue(tempItem);
    currentSize++;

    qDebug() << "Pushed to Queue";

    //usleep(10);
    // Unlock thread so queue can be accessed again
    mutex.unlock();
}
/*void queue::pushToQueue(bool pushedItem[40])
{
    // Create temporary item to store pushed item
    bool tempItem[40];

    for (int i =0; i<40; i++)
    {
        tempItem[i] = pushedItem[i];
    }

    // Lock the thread so queue can't be modified by other threads
    mutex.lock();

    // Wait until there is space in the queue
    while (currentSize == maxSize)
    {}

    // Check that the queue is not closed
    if (isOpen == false)
    {
        qDebug() << "Trying to push to a closed queue.";
    }

    // Push to queue.
    serialisedQueue.enqueue(tempItem);
    currentSize++;

    qDebug() << "Pushed to Queue";

    //usleep(10);
    // Unlock thread so queue can be accessed again
    mutex.unlock();
}*/

void queue::pullFromQueueRequest()
{
    // Create temporary queue to store items
    QQueue<QImage> tempQueue;

    // Lock the thread so queue can't be modified by other threads
    mutex.lock();

    // If there is no item then we wait until there is one
    while (imageQueue.isEmpty() && (isOpen == true))
    {
        //msleep(1);
    }

    // Get item from threadsafe queue and write the value
    currentSize--;
    QImage pulledItem = imageQueue.dequeue();

    // Unlock thread so queue can be accessed again
    mutex.unlock();

    //emit pullFromQueue(pulledItem);
}

/*
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
        //usleep(1);
    }

    // Check that the queue is not closed
    if (isOpen == false)
    {
        qDebug() << "Trying to push to a closed queue.";
    }

    // Push to queue.
    serialisedQueue.enqueue(tempItem);
    currentSize++;

    qDebug() << "Pushed to Queue";

    //usleep(10);
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
    if (serialisedQueue.isEmpty() && (isOpen == false))
    {
        //No item to retrieve
        return false;
    }

    // If there is no item then we wait until there is one
    while (serialisedQueue.isEmpty() && (isOpen == true))
    {
        //msleep(1);
    }

    // Get item from threadsafe queue and write the value
    currentSize--;
    pulledItem = serialisedQueue.dequeue();

    // Unlock thread so queue can be accessed again
    mutex.unlock();

    //Item retrieved successfully
    return true;
}
*/
