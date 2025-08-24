/*PROGRAM PROCESSOR*/
#pragma once
#include <cstdint>
#include <cstddef>
#include <array>

namespace CHIP8{

constexpr size_t STACK_SIZE = 16;
constexpr size_t DISPLAY_X = 64;
constexpr size_t DISPLAY_Y = 32;
constexpr size_t DISPLAY_SIZE = DISPLAY_X * DISPLAY_Y;
constexpr size_t GENERAL_REG_SIZE = 16;
constexpr size_t MEMORY_SIZE = 4096;
using u8 = std::uint8_t;
using u16 = std::uint16_t;

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
    using STACK_ARR = std::array<u16, STACK_SIZE>;
    using REG_ARR = std::array<u8, GENERAL_REG_SIZE>;
    using DISPLAY_ARR = std::array<u8, DISPLAY_SIZE>;
    using MEMORY_ARR = std::array<u8, MEMORY_SIZE>;
    using INSTRUCTION = Instruction;

    public:
    Proc();

    void execute(const INSTRUCTION& instruction);
    void reset();
    void setKeyPressed(const u8 key);
    [[nodiscard]] u16 fetch(const u16 memoryLocation) const;
    [[nodiscard]] INSTRUCTION decode(const u16 instruction) const;

    [[nodiscard]] inline const bool&          isKeyPressed()  const noexcept {return _isKeyPressed;};
    [[nodiscard]] inline const u8&            getKeyPressed() const noexcept {return _keyValue;};
    [[nodiscard]] inline const u8&            getDelayReg()   const noexcept {return _delayReg;};
    [[nodiscard]] inline const u8&            getSoundReg()   const noexcept {return _soundReg;};
    [[nodiscard]] inline const u8&            getSP()         const noexcept {return _SP;};
    [[nodiscard]] inline const u16&           getPC()         const noexcept {return _PC;};
    [[nodiscard]] inline const u16&           getRegI()       const noexcept {return _regI;};
    [[nodiscard]] inline const u8&            getVReg(const size_t index)     const {return _regV.at(index);};
    [[nodiscard]] inline const REG_ARR&       getAllVReg()    const noexcept {return _regV;};
    [[nodiscard]] inline const u16&           getStack(const size_t index)    const {return _stack.at(index);};
    [[nodiscard]] inline const STACK_ARR&     getAllStack()   const noexcept {return _stack;};
    [[nodiscard]] inline const DISPLAY_ARR&   getDisplay()    const noexcept {return _display;};
    [[nodiscard]] inline const MEMORY_ARR&    getMemory()     const noexcept {return _memory;};

    private:
    bool        _isKeyPressed;
    u8          _keyValue;
    u8          _delayReg;
    u8          _soundReg;
    u8          _SP;
    u16         _PC;
    u16         _regI;
    REG_ARR     _regV;
    STACK_ARR   _stack;
    DISPLAY_ARR _display;
    MEMORY_ARR  _memory;

    private:
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
};

}