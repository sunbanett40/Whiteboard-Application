#include <cmath>
#include <QDebug>

#include "receivethread.h"

receiveThread::receiveThread()
{
    qDebug() << "Receiver thread started";
    //serialQueue = sQueue;
}

void receiveThread::pullSerialStruct()
{
    mutex.lock();
    drawInfoPosition pulledItem;

    //serialQueue->pullFromQueueRequest(serialData);
    receiveThread::checkParityBit(pulledItem);
    mutex.unlock();

    bool serialsedArray[48];

    //remove when queue works
    drawInfoPosition serialData;
    serialData.opcode =0; serialData.xPosition =0; serialData.yPosition =0;

    uint16_t temp[3] = {serialData.opcode, serialData.xPosition, serialData.yPosition};

    // Loop over each element of the temporary array
    for(int i = 0; i < 3; i++)
    {
        for(int j = 15; j>= 0; j--)
        {
            // Convert to decimal
            if (serialsedArray[i*i+j])
            {
                temp[i] += pow(2,j);
            }
        }
    }

    //receiveThread::readSerialStruct(pulledItem);
}
/*
void receiveThread::readSerialStruct(command serialData)
{
    uint8_t op = serialData.opcode;

    int penWidth;
    QColor colour;
    QPoint position;

    switch (op)
    {
    case opcodes::sync:

    case opcodes::clear:

    case opcodes::setPen:
        penWidth = serialData.data1 >> 8;
        colour.setRed(serialData.data1);
        colour.setGreen(serialData.data2 >> 8);
        colour.setBlue(serialData.data2);

    case opcodes::pressEvent:
        position.setX(serialData.data1);
        position.setY(serialData.data2);
    case opcodes::moveEvent:
        position.setX(serialData.data1);
        position.setY(serialData.data2);
    case opcodes::releaseEvent:
        position.setX(serialData.data1);
        position.setY(serialData.data2);
    case opcodes::paintPixel:
        position.setX(serialData.data1);
        position.setY(serialData.data2);
    case opcodes::resize:
        position.setX(serialData.data1);
        position.setY(serialData.data2);

    default:
        this -> resend();
    }
}
*/
void receiveThread::poll()
{
    receiveThread::pullSerialStruct();
}

void receiveThread::checkParityBit(drawInfoPosition serialData)
{
    mutex.lock();
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
        this -> resend();
    }
    mutex.unlock();

}

void receiveThread::resend()
{
    mutex.lock();
    //serialQueue.pushToQueue(false);

    mutex.unlock();
}


