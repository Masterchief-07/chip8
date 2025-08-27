#pragma once
#include "chip8/display.hpp"
#include "chip8/keyboard.hpp"
#include "chip8/program.hpp"
#include "chip8/proc.hpp"

namespace CHIP8{

class Chip8
{
    public:
    Chip8(std::string_view programPath, size_t width, size_t height);

    void setScreenResolution();
    void run();

    private:
    Proc _proc;
    Display _display;
    Keyboard _keyboard;
    Program _program;

};

}
