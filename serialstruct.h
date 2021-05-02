#ifndef SERIALSTRUCT_H
#define SERIALSTRUCT_H

#include <cstdint>

typedef struct command
{
    //bit 1 parity
    //opcodes
    uint8_t opcode;

    //width
    //pen + red colour
    uint16_t data1;

    //height
    //green colour + blue colour
    uint16_t data2;

} Command;

#endif // SERIALSTRUCT_H
