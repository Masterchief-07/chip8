#pragma once
#include "chip8/interface/IProc.hpp"
#include <string_view>

namespace CHIP8{
class IProgram
{
    public:
    IProgram();

    virtual void read (std::string_view path)   = 0;
    virtual void write(IProc& processor)        = 0;
};

}