#include "chip8/proc.hpp"

Proc::Proc():
    _delayReg{0},
    _timerReg{0},
    _SP{0},
    _PC{0},
    _regI{0},
    _regV{0},
    _stack{0},
    _display{0},
    _memory{0},
{

}

void Proc::execute(Proc::u16 instruction)
{

}

void Proc::reset()
{
    _delayReg = {0};
    _timerReg = {0};
    _SP = {0};
    _PC = {0};
    _regI = {0};
    _regV = {0};
    _stack = {0};
    _display = {0};
    _memory = {0};
}