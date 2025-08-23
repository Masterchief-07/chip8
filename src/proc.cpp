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
[[nodiscard]] Proc::INSTRUCTION Proc::decode(const u16 instruction) const
{
    return {instruction};
}

void Proc::execute(const Proc::INSTRUCTION& instruction)
{
    const auto [opcode, x, y, z] = instruction.getData();
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
    std::println("unknow instruction ", instru.getInstruction());
}
void Proc::handle00E0(const INSTRUCTION& instruction)
{
    //clear display
    std::println("command: CLS ", instruction.getInstruction());
    this->_display = {0};
}

void Proc::handle00EE(const INSTRUCTION& instruction)
{
    //return function
    std::println("command: RET ", instruction.getInstruction());
    this->_PC = this->_stack.at(this->_SP);
    this->_SP = this->_SP > 1 ? this->_SP - 1 : 0;
}
void Proc::handle1nnn(const INSTRUCTION& instruction)
{
    //jump to address
    std::println("command: JP ADDR ", instruction.getInstruction());
    const auto addr = instruction.getAddr();
    this->_PC = addr < MEMORY_SIZE ? addr : _PC;

}
void Proc::handle2nnn(const INSTRUCTION& instruction)
{
    //call subroutine
    std::println("command: CALL ADDR ", instruction.getInstruction());
    const auto addr = instruction.getAddr();
    this->_SP += 1;
    this->_stack.at(this->_SP) = this->_PC;
    this->_PC = addr;

}
void Proc::handle3xkk(const INSTRUCTION& instruction)
{
    // compare equ and skip
    std::println("command: SE Vx, byte ", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto kk = instruction.getByte();
    const auto regVx = this->_regV.at(x);
    this->_PC = regVx == kk ? this->_PC + 2 : this->_PC;

}
void Proc::handle4xkk(const INSTRUCTION& instruction)
{
    // compare diff and skip
    std::println("command: SNE Vx, byte ", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto kk = instruction.getByte();
    const auto regVx = this->_regV.at(x);
    this->_PC = regVx != kk ? this->_PC + 2 : this->_PC;
}

void Proc::handle5xy0(const INSTRUCTION& instruction)
{
    // compare diff and skip
    std::println("command: SE Vx, Vy ", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto y = instruction.getY();
    const auto regVx = this->_regV.at(x);
    const auto regVy = this->_regV.at(y);
    this->_PC = regVx == regVy ? this->_PC + 2 : this->_PC;

}
void Proc::handle6xkk(const INSTRUCTION& instruction)
{
    // Load register
    std::println("command: LD Vx, byte ", instruction.getInstruction());
    const auto data = instruction.getByte();
    const auto x = instruction.getX();
    this->_regV.at(x) = data;

}
void Proc::handle7xkk(const INSTRUCTION& instruction)
{
    // ADD register
    std::println("command: ADD Vx, byte ", instruction.getInstruction());
    const auto data = instruction.getByte();
    const auto x = instruction.getX();
    this->_regV.at(x) += data;

}
void Proc::handle8xy0(const INSTRUCTION& instruction)
{
    // Load register
    std::println("command: LD Vx, Vy ", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) = this->_regV.at(y);

}
void Proc::handle8xy1(const INSTRUCTION& instruction)
{
    // OR register
    std::println("command: OR Vx, Vy ", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) |= this->_regV.at(y);

}
void Proc::handle8xy2(const INSTRUCTION& instruction)
{
    // AND register
    std::println("command: AND Vx, Vy ", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) &= this->_regV.at(y);

}
void Proc::handle8xy3(const INSTRUCTION& instruction)
{
    // XOR register
    std::println("command: AND Vx, Vy ", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) ^= this->_regV.at(y);

}
void Proc::handle8xy4(const INSTRUCTION& instruction)
{
    // ADD register
    std::println("command: AND Vx, Vy ", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) += this->_regV.at(y);

}
void Proc::handle8xy5(const INSTRUCTION& instruction)
{
    // SUB register
    std::println("command: SUB Vx, Vy ", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) -= this->_regV.at(y);

}
void Proc::handle8xy6(const INSTRUCTION& instruction)
{
    // SUB register
    std::println("command: SUB Vx, Vy ", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) -= this->_regV.at(y);

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