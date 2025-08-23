#include "chip8/proc.hpp"
#include <print>

using namespace CHIP8;

Proc::Proc():
    _delayReg{0},
    _timerReg{0},
    _SP{0},
    _PC{0},
    _regI{0},
    _regV{0},
    _stack{0},
    _display{0},
    _memory{0}
{

}
[[nodiscard]] Proc::INSTRUCTION Proc::decode(const Proc::u16 instruction) const
{
    const Proc::u8 opcode = (instruction & 0xf000) >> 12;
    const Proc::u8 x      = (instruction & 0x0f00) >> 8;
    const Proc::u8 y      = (instruction & 0x00f0) >> 4;
    const Proc::u8 z      = (instruction & 0x000f);
    return {opcode, x, y, z};
}

void Proc::execute(const Proc::INSTRUCTION& instruction)
{
    const auto [opcode, x, y, z] = instruction;
    switch(opcode)
    {
        case 0x0:
        {
            if(x == 0 && y == 0xE && z == 0)
                this->handle00E0(instruction);
            else if(x == 0 && y == 0xE && z == 0xE)
                this->handle00EE(instruction);
            else
                this->handleUnknow(instruction);

        }
        break;
        case 0x1:
        {
            this->handle1nnn(instruction);

        }
        break;
        case 0x2:
        {
            this->handle2nnn(instruction);
        }
        break;
        case 0x3:
        {
            this->handle3xkk(instruction);
        }
        break;
        case 0x4:
        {
            this->handle4xkk(instruction);
        }
        break;
        case 0x5:
        {
            this->handle5xy0(instruction);
        }
        break;
        case 0x6:
        {
            this->handle6xkk(instruction);
        }
        break;
        case 0x7:
        {
            this->handle7xkk(instruction);
        }
        break;
        case 0x8:
        {
            switch(z)
            {
                case 0x1:
                {
                    this->handle8xy1(instruction);
                }
                break;
                case 0x2:
                {
                    this->handle8xy2(instruction);
                }
                break;
                case 0x4:
                {
                    this->handle8xy4(instruction);
                }
                break;
                case 0x5:
                {
                    this->handle8xy5(instruction);
                }
                break;
                case 0x6:
                {
                    this->handle8xy6(instruction);
                }
                break;
                case 0x7:
                {
                    this->handle8xy7(instruction);
                }
                break;
                case 0xE:
                {
                    this->handle8xyE(instruction);
                }
                break;
                default:
                    this->handleUnknow(instruction);
                break;
            }
        }
        break;
        case 0x9:
        {
            this->handle9xy0(instruction);
        }
        break;
        case 0xA:
        {
            this->handleAnnn(instruction);
        }
        break;
        case 0xB:
        {
            this->handleBnnn(instruction);
        }
        break;
        case 0xC:
        {
            this->handleCxkk(instruction);
        }
        break;
        case 0xD:
        {
            this->handleDxyn(instruction);
        }
        break;
        case 0xE:
        {
            if(y == 0x9 && z == 0xE)
                this->handleEx9E(instruction);
            else if(y == 0xA && z == 0x1)
                this->handleExA1(instruction);
            else
                this->handleUnknow(instruction);
        }
        break;
        case 0xF:
        {
            switch(y)
            {
                case 0x0:
                {
                    switch(z){
                        case 0x7:
                            this->handleFx07(instruction);
                        break;
                        case 0xA:
                            this->handleFx0A(instruction);
                        break;
                        default:
                            this->handleUnknow(instruction);
                        break;
                    }

                }
                break;
                case 0x1:
                {
                    switch(z){
                        case 0x5:
                            this->handleFx15(instruction);
                        break;
                        case 0x8:
                            this->handleFx18(instruction);
                        break;
                        case 0xE:
                            this->handleFx1E(instruction);
                        break;
                        default:
                            this->handleUnknow(instruction);
                        break;
                    }
                }
                break;
                case 0x2:
                {
                    switch(z){
                        case 0x9:
                            this->handleFx29(instruction);
                        break;
                        default:
                            this->handleUnknow(instruction);
                        break;
                    }
                }
                break;
                case 0x3:
                {
                    switch(z){
                        case 0x3:
                            this->handleFx33(instruction);
                        break;
                        default:
                            this->handleUnknow(instruction);
                        break;
                    }
                }
                break;
                case 0x5:
                {
                    switch(z){
                        case 0x5:
                            this->handleFx55(instruction);
                        break;
                        default:
                            this->handleUnknow(instruction);
                        break;
                    }
                }
                break;
                case 0x6:
                {
                    switch(z){
                        case 0x5:
                            this->handleFx65(instruction);
                        break;
                        default:
                            this->handleUnknow(instruction);
                        break;
                    }
                }
                break;
                default:
                    this->handleUnknow(instruction);
                break;
            }
        }
        break;
        default:
        {
            this->handleUnknow(instruction);
        }
        break;
    }

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

void Proc::handleUnknow(const INSTRUCTION& instru)
{
    std::println("unknow instruction ", instru[0], instru[1], instru[2], instru[4]);
}
void Proc::handle00E0(const INSTRUCTION& instruction)
{

}
void Proc::handle00EE(const INSTRUCTION& instruction)
{

}
void Proc::handle1nnn(const INSTRUCTION& instruction)
{

}
void Proc::handle2nnn(const INSTRUCTION& instruction)
{

}
void Proc::handle3xkk(const INSTRUCTION& instruction)
{

}
void Proc::handle4xkk(const INSTRUCTION& instruction)
{

}
void Proc::handle5xy0(const INSTRUCTION& instruction)
{

}
void Proc::handle6xkk(const INSTRUCTION& instruction)
{

}
void Proc::handle7xkk(const INSTRUCTION& instruction)
{

}
void Proc::handle8xy1(const INSTRUCTION& instruction)
{

}
void Proc::handle8xy2(const INSTRUCTION& instruction)
{

}
void Proc::handle8xy4(const INSTRUCTION& instruction)
{

}
void Proc::handle8xy5(const INSTRUCTION& instruction)
{

}
void Proc::handle8xy6(const INSTRUCTION& instruction)
{

}
void Proc::handle8xy7(const INSTRUCTION& instruction)
{

}
void Proc::handle8xyE(const INSTRUCTION& instruction)
{

}
void Proc::handle9xy0(const INSTRUCTION& instruction)
{

}
void Proc::handleAnnn(const INSTRUCTION& instruction)
{

}
void Proc::handleBnnn(const INSTRUCTION& instruction)
{

}
void Proc::handleCxkk(const INSTRUCTION& instruction)
{

}
void Proc::handleDxyn(const INSTRUCTION& instruction)
{

}
void Proc::handleEx9E(const INSTRUCTION& instruction)
{

}
void Proc::handleExA1(const INSTRUCTION& instruction)
{

}
void Proc::handleFx07(const INSTRUCTION& instruction)
{

}
void Proc::handleFx0A(const INSTRUCTION& instruction)
{

}
void Proc::handleFx15(const INSTRUCTION& instruction)
{

}
void Proc::handleFx18(const INSTRUCTION& instruction)
{

}
void Proc::handleFx1E(const INSTRUCTION& instruction)
{

}
void Proc::handleFx29(const INSTRUCTION& instruction)
{

}
void Proc::handleFx33(const INSTRUCTION& instruction)
{

}
void Proc::handleFx55(const INSTRUCTION& instruction)
{

}
void Proc::handleFx65(const INSTRUCTION& instruction)
{

}