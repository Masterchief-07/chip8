
#pragma once
#include <cstdint>

namespace CHIP8{

using u8 = uint8_t;
using u16 = uint16_t;

enum class CHIP8KEY : u8
{
    ZERO = 0,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    A = 'a',
    B = 'b',
    C = 'c',
    D = 'd',
    E = 'e',
    F = 'f',

    NOTHING = 255,
};

}