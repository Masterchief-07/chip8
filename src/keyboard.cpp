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

std::array<CHIP8KEY, 16> Keyboard::getPressedKey() const
{
    std::array<CHIP8KEY, 16> keys{0};


    return keys;
}

std::array<CHIP8KEY, 16> Keyboard::getReleasedKey() const
{
    const auto keyPressed = GetKeyPressed();
}

void Keyboard::setKeymap(unsigned int key, CHIP8KEY target)
{
    _keymap.at(static_cast<KeyboardKey>(key)) = target;
}