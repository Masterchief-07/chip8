#pragma once

namespace CHIP8{

    class IProc{

        public:
        IProc();

        virtual void cycle() = 0;
        virtual bool getDrawFlag() = 0;

    virtual inline const bool           getDrawFlag() const = 0;
    virtual inline const KEYBOARD&      getKeyKeyboard() const = 0;
    virtual inline const u8&            getDelayReg()   const = 0;
    virtual inline const u8&            getSoundReg()   const = 0;
    virtual inline const u8&            getSP()         = 0;
    virtual inline const u16&           getPC()         = 0;
    virtual inline const u16&           getRegI()        = 0;
    virtual inline const u8&            getVReg(const size_t index)    = 0;
    virtual inline const REG_ARR&       getAllVReg()     = 0;
    virtual inline const STACK_ARR&     getAllStack()   = 0;
    virtual inline const DISPLAY_ARR&   getDisplay()    = 0;
    virtual inline const MEMORY_ARR&    getMemory()     = 0;
    // [[nodiscard]] inline const u16&           getStackTop(const size_t index)    const {return _stack.at(index);};
   };

}