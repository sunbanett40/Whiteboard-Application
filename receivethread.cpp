#include<cmath>

#include "receivethread.h"

receiveThread::receiveThread()
{

}

void receiveThread::pullSerialStruct()
{}

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

void receiveThread::checkParityBit(command serialData)
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
        this -> resend();
    }
    mutex.unlock();

}
