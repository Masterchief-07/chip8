#include "chip8/keyboard.hpp"
#include "chip8/proc.hpp"
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

void Keyboard::setKeyState(CHIP8::Proc& processor) const
{
    for(const auto &[key, chip8Key] : this->_keymap)
    {
        if(IsKeyDown(key))
            processor.setKeyboardState(chip8Key, 1);
        else if(IsKeyUp(key))
            processor.setKeyboardState(chip8Key, 0);
    }
}

void Keyboard::setKeymap(unsigned int key, CHIP8KEY target)
{
    _keymap.at(static_cast<KeyboardKey>(key)) = target;
}