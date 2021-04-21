#include "singleton.h"

void singleton::setDirty(bool dirty)
{
    dirtyBit = dirty;
}

void singleton::setOp(uint8_t op)
{
    opcode = op;
}

void singleton::setData(int pos, uint16_t data)
{
    switch(pos){
    case(1):
        data1 = data;
    case(2):
        data2 = data;
    case(3):
        data3 = data;
    case(4):
        data4 = data;
    default :
        data1=0; data2=0; data3=0; data4=0;
    }
}
