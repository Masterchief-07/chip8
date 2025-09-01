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
        //key input handle
        const auto keyStates = _keyboard.getKeyState();
        this->_proc.setKeyboardState(keyStates);

        //execute
        const auto opcode= _proc.fetch();
        const auto instruction = _proc.decode(opcode);
        _proc.execute(instruction);

        //draw
        _display.draw();
    }

}