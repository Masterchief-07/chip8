#include <print>
#include "chip8/chip8.hpp"

auto main(int argc, char* argv[]) -> int{

    CHIP8::Chip8 chip8{"Space Invaders [David Winter].ch8", 1920, 1080};

    chip8.run();
    return 0;
}