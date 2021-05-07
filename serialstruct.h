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

enum opcodes
{
    sync = 1,
    clear = 2,

    setPen = 3,

    pressEvent = 4,
    moveEvent = 5,
    releaseEvent = 6,
    paintPixel = 7,

    resize =8
};

#endif // SERIALSTRUCT_H
