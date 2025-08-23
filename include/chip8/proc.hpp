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
    private:
    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using STACK_ARR = std::array<u16, STACK_SIZE>;
    using REG_ARR = std::array<u8, GENERAL_REG_SIZE>;
    using DISPLAY_ARR = std::array<u8, DISPLAY_SIZE>;
    using MEMORY_ARR = std::array<u8, MEMORY_SIZE>;

    public:
    Proc();
    void execute(u16 instruction);
    void reset();

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



};

}