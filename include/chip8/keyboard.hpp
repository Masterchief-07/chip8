/*PROGRAM KEYBOARD*/
#pragma once
#include "chip8/common.hpp"
#include <unordered_map>
namespace CHIP8{

class Keyboard{

    public:

    public:
    Keyboard();
    ~Keyboard(){};

    void setKeymap(unsigned int key, CHIP8KEY target);
    [[nodiscard]] std::array<CHIP8KEY, 16> getPressedKey() const;
    [[nodiscard]] std::array<CHIP8KEY, 16> getReleasedKey() const;

    private:
    std::unordered_map<char, CHIP8KEY> _keymap;

};

}