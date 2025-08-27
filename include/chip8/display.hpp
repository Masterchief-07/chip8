
#pragma once
#include "chip8/proc.hpp"

namespace CHIP8{

class Display
{
    public:
    Display(const Proc& proc, size_t width, size_t height);
    ~Display();
    void draw();
    void setScreenResolution(size_t x, size_t y);
    bool isWindowOpen();
    [[nodiscard]]const size_t& getWidth() const noexcept {return _width;};
    [[nodiscard]]const size_t& getHeight() const noexcept {return _height;};

    private:
    const Proc& _proc;
    size_t _width, _height;
};

}