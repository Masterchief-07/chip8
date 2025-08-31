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
    [[nodiscard]] CHIP8KEY getPressedKey() const;

    private:
    std::unordered_map<char, CHIP8KEY> _keymap;

};

}