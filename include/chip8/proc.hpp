/*PROGRAM PROCESSOR*/
#pragma once
#include <cstdint>
#include <cstddef>
#include <array>

namespace CHIP8{

constexpr size_t STACK_SIZE = 16;
constexpr size_t DISPLAY_SIZE = 64 * 32;
constexpr size_t GENERAL_REG_SIZE = 16;
constexpr size_t MEMORY_SIZE = 4096;

class Proc{
    public:
    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using STACK_ARR = std::array<u16, STACK_SIZE>;
    using REG_ARR = std::array<u8, GENERAL_REG_SIZE>;
    using DISPLAY_ARR = std::array<u8, DISPLAY_SIZE>;
    using MEMORY_ARR = std::array<u8, MEMORY_SIZE>;
    using INSTRUCTION = std::array<u8, 4>;

    public:
    Proc();

    void execute(const INSTRUCTION& instruction);
    void reset();
    [[nodiscard]] INSTRUCTION decode(const u16 instruction) const;

    [[nodiscard]] inline const u8&            getDelayReg()   const {return _delayReg;};
    [[nodiscard]] inline const u8&            getTimerReg()   const {return _timerReg;};
    [[nodiscard]] inline const u8&            getSP()         const {return _SP;};
    [[nodiscard]] inline const u16&           getPC()         const {return _PC;};
    [[nodiscard]] inline const u16&           getRegI()       const {return _regI;};
    [[nodiscard]] inline const u8&            getVReg(const size_t index)     const {return _regV.at(index);};
    [[nodiscard]] inline const REG_ARR&       getAllVReg()    const {return _regV;};
    [[nodiscard]] inline const u16&           getStack(const size_t index)    const {return _stack.at(index);};
    [[nodiscard]] inline const STACK_ARR&     getAllStack()   const {return _stack;};
    [[nodiscard]] inline const DISPLAY_ARR&   getDisplay()    const {return _display;};
    [[nodiscard]] inline const MEMORY_ARR&    getMemory()     const {return _memory;};

    private:
    u8          _delayReg;
    u8          _timerReg;
    u8          _SP;
    u16         _PC;
    u16         _regI;
    REG_ARR     _regV;
    STACK_ARR   _stack;
    DISPLAY_ARR _display;
    MEMORY_ARR  _memory;

    private:

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
    void handle8xy1(const INSTRUCTION&);
    void handle8xy2(const INSTRUCTION&);
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