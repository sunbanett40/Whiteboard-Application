#include <cmath>

#include "sendthread.h"

sendThread::sendThread(queue *sQueue)
{
    serialQueue = sQueue;
}

void sendThread::pushSerialStruct(QImage serialData)
{
    //this -> setParityBit(serialData);

    mutex.lock();
    serialQueue->pushToQueue(serialData);

    mutex.unlock();

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
