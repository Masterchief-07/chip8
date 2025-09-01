#include "chip8/display.hpp"
#include "chip8/proc.hpp"
#include "raylib.h"

using namespace CHIP8;

Display::Display(const Proc& proc, size_t width, size_t height): _proc{proc}, _width{width}, _height{height}
{
    InitWindow(width, height, "CHIP8");
    // SetTargetFPS(120);
}

Display::~Display()
{
    CloseWindow();
}

void Display::draw()
{
    BeginDrawing();

    ClearBackground(BLACK);
    const int widthDim = _width / DISPLAY_X;
    const int heightDim = _height / DISPLAY_Y;
    for(size_t y = 0; y < DISPLAY_Y; y++)
    {
        for(size_t x = 0; x < DISPLAY_X; x++)
        {
            const size_t data_position = y * DISPLAY_X + x;
            const auto data = this->_proc.getDisplay().at(data_position);
            DrawRectangle(x * widthDim, y*heightDim, widthDim, heightDim, data > 0 ? RAYWHITE : BLACK);
        }

    }

    EndDrawing();
}

bool Display::isWindowOpen()
{
    return !WindowShouldClose();
}

void Display::setScreenResolution(size_t width, size_t height)
{
    this->_width = width;
    this->_height = height;
}