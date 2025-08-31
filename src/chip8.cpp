#include "chip8/chip8.hpp"

using namespace CHIP8;

Chip8::Chip8(std::string_view programPath, size_t width, size_t height): 
                                                                    _proc{},
                                                                    _display{_proc, width, height},
                                                                    _keyboard{},
                                                                    _program{programPath}
{
    this->_proc.setPC(0x200);
    this->_proc.setProgramToMemory(this->_program.read<MEMORY_SIZE>());
}

void Chip8::run()
{
    while(_display.isWindowOpen())
    {

        //execute
        const auto opcode= _proc.fetch();
        const auto instruction = _proc.decode(opcode);
        _proc.execute(instruction);

        //key input handle
        const auto keyPressed = this->_keyboard.getPressedKey();
        _proc.setKeyPressed(keyPressed);
        //release keyboard
        const auto keyReleased = this->_keyboard.getReleasedKey();
        _proc.setKeyPressed(keyReleased);

        //draw
        _display.draw();
    }

}