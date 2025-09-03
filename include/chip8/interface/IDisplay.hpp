#pragma once
#include "chip8/interface/IProc.hpp"
#include <cstddef>

namespace CHIP8{

class IDisplay
{
    public:
    IDisplay();

    virtual void setScreenResolution(size_t x, size_t y) = 0;
    virtual void draw(const IProc& processor) = 0;
};

}