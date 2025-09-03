#pragma once
#include "chip8/interface/IProc.hpp"
#include <cstddef>

namespace CHIP8{

class IKeyboard
{
    public:
    IKeyboard();

    virtual void setKeyState(IProc& processor)          = 0;
    virtual void setKeymap  (size_t key, size_t target) = 0;

};

}