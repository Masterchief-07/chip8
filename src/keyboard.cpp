#include "chip8/keyboard.hpp"
#include "raylib.h"

using namespace CHIP8;

Keyboard::Keyboard(): _keymap{{
    {KEY_ONE, CHIP8KEY::ONE},   {KEY_TWO, CHIP8KEY::TWO},   {KEY_THREE, CHIP8KEY::THREE},{KEY_FOUR, CHIP8KEY::C},
    {KEY_Q, CHIP8KEY::FOUR},    {KEY_W, CHIP8KEY::FIVE},    {KEY_E, CHIP8KEY::SIX},     {KEY_R, CHIP8KEY::D},
    {KEY_A, CHIP8KEY::SEVEN},   {KEY_S, CHIP8KEY::EIGHT},   {KEY_D, CHIP8KEY::NINE},    {KEY_F, CHIP8KEY::E},
    {KEY_Z, CHIP8KEY::A},       {KEY_X, CHIP8KEY::ZERO},    {KEY_C, CHIP8KEY::B},       {KEY_V, CHIP8KEY::F},
}}
{

}

std::array<u8, 16> Keyboard::getKeyState() const
{
    std::array<u8, 16L> keys{};
    for(const auto &[key, chip8Key] : this->_keymap)
    {
        if(IsKeyDown(key))
            keys[static_cast<u8>(chip8Key)] = 0x01;
        else
            keys[static_cast<u8>(chip8Key)] = 0x00;
    }

    return keys;
}

void Keyboard::setKeymap(unsigned int key, CHIP8KEY target)
{
    _keymap.at(static_cast<KeyboardKey>(key)) = target;
}