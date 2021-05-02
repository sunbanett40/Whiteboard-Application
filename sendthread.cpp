#include "sendthread.h"

sendThread::sendThread()
{

}

command sendThread::setSerialStruct(uint8_t op, QPoint pos)
{
    mutex.lock();
    command serialData;
    serialData.opcode = op;
    serialData.data1 = pos.x();
    serialData.data2 = pos.y();

    mutex.unlock();
    return serialData;
}

command sendThread::setSerialStruct(uint8_t op, int penWidth, QColor penColour)
{
    uint8_t width = penWidth;
    uint8_t red = penColour.red();
    uint8_t green = penColour.green();;
    uint8_t blue = penColour.blue();;

    mutex.lock();
    command serialData;
    serialData.opcode = op;

    // Combine information into the two data bits
    //https://stackoverflow.com/questions/15249791/combining-two-uint8-t-as-uint16-t
    serialData.data1 = (width << 8) | red;
    serialData.data2 = (green << 8) | blue;

    mutex.unlock();
    return serialData;
}

void sendThread::sendSerialStruct(command serialData)
{
    mutex.lock();


    serialQueue.enqueue(serialData);
    mutex.unlock();


}

void sendThread::setParityBit(command serialData)
{
    mutex.lock();

    mutex.unlock();
}
