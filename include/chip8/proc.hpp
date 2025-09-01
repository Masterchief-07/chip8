/*PROGRAM PROCESSOR*/
#pragma once
#include "chip8/common.hpp"
#include <cstddef>
#include <array>
#include <stack>

namespace CHIP8{

constexpr size_t STACK_SIZE = 16;
constexpr size_t DISPLAY_X = 64;
constexpr size_t DISPLAY_Y = 32;
constexpr size_t DISPLAY_SIZE = DISPLAY_X * DISPLAY_Y;
constexpr size_t GENERAL_REG_SIZE = 16;
constexpr size_t MEMORY_SIZE = 4096;
constexpr size_t DIGITSPRITE_SIZE = 16 * 5;

struct Instruction
{
    Instruction(const u16 instruction):_instruction{instruction}{}
    [[nodiscard]] inline u8     getNible() const noexcept{return _instruction & 0x000f;}
    [[nodiscard]] inline u8     getOpCode() const noexcept{return (_instruction & 0xf000) >> 12;}
    [[nodiscard]] inline u8     getX() const noexcept    {return (_instruction & 0x0f00) >> 8;}
    [[nodiscard]] inline u8     getY() const noexcept    {return (_instruction & 0x00f0) >> 4;}
    [[nodiscard]] inline u8     getByte() const noexcept {return (_instruction & 0x00ff);}
    [[nodiscard]] inline u16    getAddr() const noexcept {return (_instruction & 0x0fff);}
    [[nodiscard]] inline u16    getInstruction() const noexcept {return _instruction;}
    [[nodiscard]] inline const std::array<u8, 4> getData() const noexcept {return {getOpCode(), getX(), getY(), getNible()};}

    private:
    u16 _instruction;

};

class Proc{
    public:
    using STACK_ARR = std::stack<u16>;
    using REG_ARR = std::array<u8, GENERAL_REG_SIZE>;
    using DISPLAY_ARR = std::array<u8, DISPLAY_SIZE>;
    using MEMORY_ARR = std::array<u8, MEMORY_SIZE>;
    using DIGITSPRITE = std::array<u8, DIGITSPRITE_SIZE>;
    using KEYBOARD = std::array<u8, 16>;
    using INSTRUCTION = Instruction;

    public:
    Proc();

    void execute(const INSTRUCTION& instruction);
    void reset();
    void setPC(const u16 key);
    void setKeyboardState(const std::array<u8, 16>& key);
    void setKeyboardState(const CHIP8KEY key, const u8 value);
    void setProgramToMemory(const MEMORY_ARR& data);
    [[nodiscard]] u16 fetch() const;
    [[nodiscard]] INSTRUCTION decode(const u16 instruction) const;

    [[nodiscard]] inline const bool           getDrawFlag() const noexcept {return _drawFlag;};
    [[nodiscard]] inline const KEYBOARD&      getKeyKeyboard() const noexcept {return _keyValue;};
    [[nodiscard]] inline const u8&            getDelayReg()   const noexcept {return _delayReg;};
    [[nodiscard]] inline const u8&            getSoundReg()   const noexcept {return _soundReg;};
    [[nodiscard]] inline const u8&            getSP()         const noexcept {return _SP;};
    [[nodiscard]] inline const u16&           getPC()         const noexcept {return _PC;};
    [[nodiscard]] inline const u16&           getRegI()       const noexcept {return _regI;};
    [[nodiscard]] inline const u8&            getVReg(const size_t index)     const {return _regV.at(index);};
    [[nodiscard]] inline const REG_ARR&       getAllVReg()    const noexcept {return _regV;};
    // [[nodiscard]] inline const u16&           getStackTop(const size_t index)    const {return _stack.at(index);};
    [[nodiscard]] inline const STACK_ARR&     getAllStack()   const noexcept {return _stack;};
    [[nodiscard]] inline const DISPLAY_ARR&   getDisplay()    const noexcept {return _display;};
    [[nodiscard]] inline const MEMORY_ARR&    getMemory()     const noexcept {return _memory;};

    private:
    bool        _drawFlag;
    u8          _delayReg;
    u8          _soundReg;
    u8          _SP;
    u16         _PC;
    u16         _regI;
    REG_ARR     _regV;
    STACK_ARR   _stack;
    DISPLAY_ARR _display;
    MEMORY_ARR  _memory;
    KEYBOARD    _keyValue;
    const DIGITSPRITE _digitSprite{{
        0xf0, 0x90, 0x90, 0x90, 0xf0, //0
        0x20, 0x60, 0x20, 0x20, 0x70, //1
        0xf0, 0x10, 0xf0, 0x80, 0xf0, //2
        0xf0, 0x10, 0xf0, 0x10, 0xf0, //3
        0x90, 0x90, 0xf0, 0x10, 0x10, //4
        0xf0, 0x80, 0xf0, 0x10, 0xf0, //5
        0xf0, 0x80, 0xf0, 0x90, 0xf0, //6
        0xf0, 0x10, 0x20, 0x40, 0x40, //7
        0xf0, 0x90, 0xf0, 0x90, 0xf0, //8
        0xf0, 0x90, 0xf0, 0x10, 0xf0, //9
        0xf0, 0x90, 0xf0, 0x90, 0x90, //A
        0xe0, 0x90, 0xe0, 0x90, 0xe0, //B
        0xf0, 0x80, 0x80, 0x80, 0xf0, //C
        0xe0, 0x90, 0x90, 0x90, 0xe0, //D
        0xf0, 0x80, 0xf0, 0x80, 0xf0, //E
        0xf0, 0x80, 0x90, 0x80, 0x80, //F
    }};


    private:
    void incrementPC();
    void writeDisplay(const u8 posX, const u8 posY, const u16 memory_pos, const u8 size);
    u16 getSpriteMemoryLocation(const u8 number);
    void handleUnknow(const INSTRUCTION&);
    void handle00E0(const INSTRUCTION&);
    void handle00EE(const INSTRUCTION&);
    void handle1nnn(const INSTRUCTION&);
    void handle2nnn(const INSTRUCTION&);
    void handle3xkk(const INSTRUCTION&);
    void handle4xkk(const INSTRUCTION&);
    void handle5xy0(const INSTRUCTION&);
    void handle6xkk(const INSTRUCTION&);
    void handle7xkk(const INSTRUCTION&);
    void handle8xy0(const INSTRUCTION&);
    void handle8xy1(const INSTRUCTION&);
    void handle8xy2(const INSTRUCTION&);
    void handle8xy3(const INSTRUCTION&);
    void handle8xy4(const INSTRUCTION&);
    void handle8xy5(const INSTRUCTION&);
    void handle8xy6(const INSTRUCTION&);
    void handle8xy7(const INSTRUCTION&);
    void handle8xyE(const INSTRUCTION&);
    void handle9xy0(const INSTRUCTION&);
    void handleAnnn(const INSTRUCTION&);
    void handleBnnn(const INSTRUCTION&);
    void handleCxkk(const INSTRUCTION&);
    void handleDxyn(const INSTRUCTION&);
    void handleEx9E(const INSTRUCTION&);
    void handleExA1(const INSTRUCTION&);
    void handleFx07(const INSTRUCTION&);
    void handleFx0A(const INSTRUCTION&);
    void handleFx15(const INSTRUCTION&);
    void handleFx18(const INSTRUCTION&);
    void handleFx1E(const INSTRUCTION&);
    void handleFx29(const INSTRUCTION&);
    void handleFx33(const INSTRUCTION&);
    void handleFx55(const INSTRUCTION&);
    void handleFx65(const INSTRUCTION&);

    void logState();
};

}
