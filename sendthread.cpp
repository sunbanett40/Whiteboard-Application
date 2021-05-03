#include <cmath>

#include "sendthread.h"

sendThread::sendThread()
{
    //serialQueue = &;
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

void sendThread::pushSerialStruct(command serialData)
{
    this -> setParityBit(serialData);

    /*do
    {
    mutex.lock();
    serialQueue.enqueue(serialData);

    mutex.unlock();
    }
    while (serialQueue.pullFromQueue == false)
    {
    mutex.lock();
    serialQueue.enqueue(serialData);
    mutex.unlock();
    }*/
}

void sendThread::setParityBit(command serialData)
{
    mutex.lock();
    int bitCount = 0;
    uint16_t temp[3] = {serialData.opcode, serialData.data1, serialData.data2};

    // Loop over each element of the temporary array
    for(int i = 0; i < 3; i++)
    {
        for(int j = 15; j>= 0; j--)
        {
            // Convert to binary
            if (temp[i] >= pow(2, j))
            {

                temp[i] -= pow(2, j);

                // Increase Local Count
                bitCount++;
            }
        }
    }

    // If odd number of bits
    if(bitCount % 2 != 0)
    {
        // Set Parity Bit
        serialData.opcode |= (1 << 7);
    }
    mutex.unlock();
}
