#include <cmath>
#include <QDebug>

#include "sendthread.h"

sendThread::sendThread()
{
    qDebug() << "Sender thread started";
    //serialQueue = sQueue;
}

void sendThread::pushSerialStruct(drawInfoPosition serialData)
{
    this -> setParityBit(serialData);

    uint16_t temp[3] = {serialData.opcode, serialData.xPosition, serialData.yPosition};
    bool serialsedArray[48] = {};

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
                serialsedArray[i*j+j] = true;
            }
        }
    }

    mutex.lock();

    //qDebug() << "Information on wire: " << Qt::bin << serialData.opcode << Qt::bin << serialData.xPosition << Qt::bin << serialData.yPosition;

    //serialQueue->pushToQueue(serialData);
    mutex.unlock();

}
void sendThread::pushSerialStruct(drawInfoPen serialData)
{
    //this -> setParityBit(serialData);

    mutex.lock();
    //serialQueue->pushToQueue(serialData);

    mutex.unlock();

}

void sendThread::setParityBit(drawInfoPosition serialData)
{
    int bitCount = 0;
    uint16_t temp[3] = {serialData.opcode, serialData.xPosition, serialData.yPosition};

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
}
