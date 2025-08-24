#include "chip8/proc.hpp"
#include <print>
#include <cstdlib>

using namespace CHIP8;

Proc::Proc():
    _isKeyPressed{false},
    _keyValue{0},
    _delayReg{0},
    _soundReg{0},
    _SP{0},
    _PC{0},
    _regI{0},
    _regV{0},
    _stack{0},
    _display{0},
    _memory{0}
{

}

void Proc::reset()
{
    _delayReg = {0};
    _soundReg = {0};
    _SP = {0};
    _PC = {0};
    _regI = {0};
    _regV = {0};
    _stack = {0};
    _display = {0};
    _memory = {0};
    _isKeyPressed = {false};
    _keyValue = {0};
}

[[nodiscard]] Proc::INSTRUCTION Proc::decode(const u16 instruction) const
{
    return {instruction};
}

void Proc::setKeyPressed(const u8 key)
{
    this->_isKeyPressed = true;
    this->_keyValue = key;
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
                case 0x0:
                    this->handle8xy0(instruction);
                break;
                case 0x1:
                    this->handle8xy1(instruction);
                break;
                case 0x2:
                    this->handle8xy2(instruction);
                break;
                case 0x3:
                    this->handle8xy3(instruction);
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

void Proc::handleUnknow(const INSTRUCTION& instru)
{
    std::println("unknow instruction {:#06x}", instru.getInstruction());
}
void Proc::handle00E0(const INSTRUCTION& instruction)
{
    //clear display
    std::println("command: CLS {:#0x}", instruction.getInstruction());
    this->_display = {0};
    //next instruction
    this->_PC +=1;
}

void Proc::handle00EE(const INSTRUCTION& instruction)
{
    //return function
    std::println("command: RET {:#0x}", instruction.getInstruction());
    this->_PC = this->_stack.at(this->_SP);
    this->_SP = this->_SP > 1 ? this->_SP - 1 : 0;
}
void Proc::handle1nnn(const INSTRUCTION& instruction)
{
    //jump to address
    std::println("command: JP ADDR {:#0x}", instruction.getInstruction());
    const auto addr = instruction.getAddr();
    this->_PC = addr < MEMORY_SIZE ? addr : _PC + 1;

}
void Proc::handle2nnn(const INSTRUCTION& instruction)
{
    //call subroutine
    std::println("command: CALL ADDR {:#0x}", instruction.getInstruction());
    const auto addr = instruction.getAddr();
    this->_SP += 1;
    this->_stack.at(this->_SP) = this->_PC;
    this->_PC = addr;

}
void Proc::handle3xkk(const INSTRUCTION& instruction)
{
    // compare equ and skip
    std::println("command: SE Vx, byte {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto kk = instruction.getByte();
    const auto regVx = this->_regV.at(x);
    this->_PC = regVx == kk ? this->_PC + 2 : this->_PC + 1;

}
void Proc::handle4xkk(const INSTRUCTION& instruction)
{
    // compare diff and skip
    std::println("command: SNE Vx, byte {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto kk = instruction.getByte();
    const auto regVx = this->_regV.at(x);
    this->_PC = regVx != kk ? this->_PC + 2 : this->_PC + 1;
}

void Proc::handle5xy0(const INSTRUCTION& instruction)
{
    // compare equal and skip
    std::println("command: SE Vx, Vy {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto y = instruction.getY();
    const auto regVx = this->_regV.at(x);
    const auto regVy = this->_regV.at(y);
    this->_PC = regVx == regVy ? this->_PC + 2 : this->_PC + 1;

}
void Proc::handle6xkk(const INSTRUCTION& instruction)
{
    // Load register
    std::println("command: LD Vx, byte {:#0x}", instruction.getInstruction());
    const auto data = instruction.getByte();
    const auto x = instruction.getX();
    this->_regV.at(x) = data;
    //next instruction
    this->_PC +=1;

}
void Proc::handle7xkk(const INSTRUCTION& instruction)
{
    // ADD register
    std::println("command: ADD Vx, byte {:#0x}", instruction.getInstruction());
    const auto data = instruction.getByte();
    const auto x = instruction.getX();
    this->_regV.at(x) += data;
    //next instruction
    this->_PC +=1;

}
void Proc::handle8xy0(const INSTRUCTION& instruction)
{
    // Load register
    std::println("command: LD Vx, Vy {:#0x}", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) = this->_regV.at(y);
    //next instruction
    this->_PC +=1;

}
void Proc::handle8xy1(const INSTRUCTION& instruction)
{
    // OR register
    std::println("command: OR Vx, Vy {:#0x}", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) |= this->_regV.at(y);
    //next instruction
    this->_PC +=1;

}
void Proc::handle8xy2(const INSTRUCTION& instruction)
{
    // AND register
    std::println("command: AND Vx, Vy {:#0x}", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) &= this->_regV.at(y);
    //next instruction
    this->_PC +=1;

}
void Proc::handle8xy3(const INSTRUCTION& instruction)
{
    // XOR register
    std::println("command: AND Vx, Vy {:#0x}", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) ^= this->_regV.at(y);
    //next instruction
    this->_PC +=1;

}
void Proc::handle8xy4(const INSTRUCTION& instruction)
{
    // ADD register
    std::println("command: AND Vx, Vy {:#0x}", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) += this->_regV.at(y);
    //next instruction
    this->_PC +=1;

}
void Proc::handle8xy5(const INSTRUCTION& instruction)
{
    // SUB register
    std::println("command: SUB Vx, Vy {:#0x}", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) -= this->_regV.at(y);
    //next instruction
    this->_PC +=1;

}
void Proc::handle8xy6(const INSTRUCTION& instruction)
{
    // SHR register
    std::println("command: SHR Vx{:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto value = this->_regV.at(x);
    this->_regV.at(x) = value >> 1; 
    this->_regV.at(15) = value & 0b00000001; //Vf
    //next instruction
    this->_PC +=1;
}
void Proc::handle8xy7(const INSTRUCTION& instruction)
{
    // SUBN register
    std::println("command: SUBN Vx, Vy {:#0x}", instruction.getInstruction());
    const auto y = instruction.getY();
    const auto x = instruction.getX();
    this->_regV.at(x) = this->_regV.at(y) - this->_regV.at(x);
    //next instruction
    this->_PC +=1;
}
void Proc::handle8xyE(const INSTRUCTION& instruction)
{
    // SHL register
    std::println("command: SHL Vx {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto value = this->_regV.at(x);
    this->_regV.at(x) = value << 1; 
    this->_regV.at(15) = (value & 0b10000000) >> 8; //Vf
    //next instruction
    this->_PC +=1;
}
void Proc::handle9xy0(const INSTRUCTION& instruction)
{
    // compare equal and skip
    std::println("command: SE Vx, Vy {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto y = instruction.getY();
    const auto regVx = this->_regV.at(x);
    const auto regVy = this->_regV.at(y);
    this->_PC = regVx != regVy ? this->_PC + 2 : this->_PC + 1;

}
void Proc::handleAnnn(const INSTRUCTION& instruction)
{
    // LOAD I, addr
    std::println("command: LD I, addr {:#0x}", instruction.getInstruction());
    const auto addr = instruction.getAddr();
    this->_regI = addr;
    //next instruction
    this->_PC +=1;

}
void Proc::handleBnnn(const INSTRUCTION& instruction)
{
    // JUMP V0, addr
    std::println("command: JP V0, addr {:#0x}", instruction.getInstruction());
    const auto addr = instruction.getAddr();
    const auto V0 = this->_regV.at(0);
    this->_PC = V0 + addr;

}
void Proc::handleCxkk(const INSTRUCTION& instruction)
{
    // RANDOM Vx, Byte
    std::println("command: RND Vx, Byte {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto value = instruction.getByte();
    const auto random = static_cast<u8>(std::rand());
    auto& Vx = this->_regV.at(x);
    Vx = random + value;
    //next instruction
    this->_PC +=1;

}
void Proc::handleDxyn(const INSTRUCTION& instruction)
{
    // Display Vx, Vy, nibble
    std::println("command: DRW Vx, Vy, nibble {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto y = instruction.getY();
    const auto n = instruction.getNible();
    const auto Vx = this->_regV.at(x);
    const auto Vy = this->_regV.at(y);
    const auto memoryPosition = this->getRegI();
    this->writeDisplay(Vx, Vy, memoryPosition, n);
    //next instruction
    this->_PC +=1;
}
void Proc::handleEx9E(const INSTRUCTION& instruction)
{
    // key not pressed Vx
    std::println("command: SKP Vx{:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto Vx = this->_regV.at(x);
    if(_isKeyPressed && Vx != this->_keyValue)
        this->_PC += 2;
    else
        this->_PC += 1;
}
void Proc::handleExA1(const INSTRUCTION& instruction)
{
    // key pressed Vx
    std::println("command: SKNP Vx{:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto Vx = this->_regV.at(x);
    if(_isKeyPressed && Vx == this->_keyValue)
        this->_PC += 2;
    else
        this->_PC += 1;
}
void Proc::handleFx07(const INSTRUCTION& instruction)
{
    // LOAD Vx, Dt
    std::println("command: LD Vx, Dt {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto Dt = this->_delayReg;
    auto& Vx = this->_regV.at(x);
    Vx = Dt;
    this->_PC += 1; //next instruction
}
void Proc::handleFx0A(const INSTRUCTION& instruction)
{
    // LOAD Vx, key_pressed
    std::println("command: LD Vx, k {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    if(!this->_isKeyPressed)
        return;
    auto& Vx = this->_regV.at(x);
    Vx = this->_keyValue;
    this->_PC += 1; //next instruction

}
void Proc::handleFx15(const INSTRUCTION& instruction)
{
    // LOAD Dt, Vx
    std::println("command: LD Dt, Vx {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto Vx = this->_regV.at(x);
    auto& Dt = this->_delayReg;
    Dt = Vx;
    this->_PC += 1; //next instruction

}
void Proc::handleFx18(const INSTRUCTION& instruction)
{
    // LOAD St, Vx
    std::println("command: LD St, Vx {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto Vx = this->_regV.at(x);
    auto& St = this->_soundReg;
    St = Vx;
    this->_PC += 1; //next instruction

}
void Proc::handleFx1E(const INSTRUCTION& instruction)
{
    // ADD I, Vx
    std::println("command: ADD I, Vx {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto Vx = this->_regV.at(x);
    this->_regI += Vx;
    this->_PC += 1; //next instruction
}
void Proc::handleFx29(const INSTRUCTION& instruction)
{
    // LOAD F, Vx
    std::println("command: LD St, Vx {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto Vx = this->_regV.at(x);
    auto& I = this->_regI;
    I = this->getSpriteMemoryLocation(Vx);
    this->_PC += 1; //next instruction

}
void Proc::handleFx33(const INSTRUCTION& instruction)
{
    // LOAD BCD, Vx
    std::println("command: LD B, Vx {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto regI = this->_regI;
    auto Vx = this->_regV.at(x);
    // convert BCD
    const auto val1 = Vx % 10; Vx/=10; 
    const auto val2 = Vx % 10; Vx/=10;
    const auto val3 = Vx % 10; Vx/=10;
    //save in memory
    this->_memory.at(regI)      = val3;
    this->_memory.at(regI + 1)  = val2;
    this->_memory.at(regI + 2)  = val1;
    //next instruction
    this->_PC +=1;
}
void Proc::handleFx55(const INSTRUCTION& instruction)
{
    // LOAD Memory, Vx
    std::println("command: LD Memory, V0...Vx {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto regI = this->_regI;
    for(size_t i = 0; i <= x; i++)
    {
        this->_memory.at(regI + i) = this->_regV.at(i);
    }
    //next instruction
    this->_PC +=1;
}
void Proc::handleFx65(const INSTRUCTION& instruction)
{
    // LOAD V0...Vx, Memory
    std::println("command: LD V0...Vx, Memory {:#0x}", instruction.getInstruction());
    const auto x = instruction.getX();
    const auto regI = this->_regI;
    for(size_t i = 0; i <= x; i++)
    {
        this->_regV.at(i) = this->_memory.at(regI + i);
    }
    //next instruction
    this->_PC +=1;

}

void Proc::writeDisplay(const u8 posX, const u8 posY, const u16 memory_pos, const u8 size)
{
    //todo
    for(size_t i=0; i < size; i++)
    {
        const auto position = posY * DISPLAY_X + posX + i;
        std::ignore = position;

    }
}

u16 Proc::getSpriteMemoryLocation(const u8 number)
{
    //todo
    std::ignore = number;
    return 0;
}