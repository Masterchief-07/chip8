
#pragma once
#include <cstdint>

namespace CHIP8{

using u8 = uint8_t;
using u16 = uint16_t;

enum class CHIP8KEY : u8
{
    ZERO = 0x00,
    ONE = 0x01,
    TWO = 0x02,
    THREE = 0x03,
    FOUR = 0x04,
    FIVE = 0x05,
    SIX = 0x06,
    SEVEN = 0x07,
    EIGHT = 0x08,
    NINE = 0x09,
    A = 0x0A,
    B = 0x0B,
    C = 0x0C,
    D = 0x0D,
    E = 0x0E,
    F = 0x0F,

    NOTHING = 0xff,
};

}