/*
Project:    Whiteboard Chat Application - P20 Qt Project
Author:     Joseph Butterworth
License:    This work is licensed under the Creative Commons Attribution-ShareAlike License.
            View this license at https://creativecommons.org/licenses/
*/


#ifndef DRAWINFORMATION_H
#define DRAWINFORMATION_H

// For uint8 & uint16
#include <cstdint>
/*
enum opcodes
{
    // Sends position data
    pressEvent = 1,
    moveEvent = 2,
    releaseEvent = 3,

    // Uses postion format to store size
    resize =4,

    // Sends pen data
    setPen = 5,
};*/

// Struct combines all the necessary information for draw event
typedef struct drawInfoPosition
{
    // Opcodes
    // Bit 1 for odd-on parity
    uint8_t opcode;

    // Vertical and Horizontal Positions
    uint16_t xPosition;
    uint16_t yPosition;

} drawInfoPosition;

// Struct combines all the necessary information for a pen change event
typedef struct drawInfoPen
{
    // Opcodes
    // Bit 1 for odd-on parity
    uint8_t opcode;

    // Pen width
    uint8_t width;

    // RGB values
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} drawInfoPen;

#endif // DRAWINFORMATION_H
