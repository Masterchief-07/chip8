/*PROGRAM READER*/
#pragma once
#include "chip8/common.hpp"
#include <string>
#include <array>
#include <fstream>

namespace CHIP8{

class Program{
    public:
    Program(std::string_view path);
    ~Program();

    template<size_t dataSize>
    std::array<u8, dataSize> read();
    void open(std::string_view path);

    private:
    std::string _programPath;
    std::ifstream _streamData;
};

template<size_t dataSize>
std::array<u8, dataSize> Program::read()
{
    std::array<u8, dataSize> buffer{0};
    if(const auto result = this->_streamData.readsome(reinterpret_cast<char*>(buffer.data()), dataSize);
        dataSize >= static_cast<size_t>(result))
        return buffer;
    throw std::runtime_error(std::format("[PROGRAM] CAN'T READ FILE: {}", this->_programPath));
}
}