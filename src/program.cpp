#include "chip8/program.hpp"
#include <stdexcept>

using namespace CHIP8;

Program::Program(std::string_view path)
{
    this->open(path);
}

Program::~Program()
{
    if(this->_streamData.is_open())
        this->_streamData.close();
}
void Program::open(std::string_view path)
{
    this->_programPath = path;
    if(_streamData.is_open())
        this->_streamData.close();
    this->_streamData.open(this->_programPath, std::ios::binary);
    if(!_streamData.is_open())
        throw std::runtime_error(std::format("[PROGRAM]CAN'T OPEN FILE: {}", path));
}
