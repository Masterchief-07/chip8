#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include "chip8/proc.hpp"
#include <print>

TEST_CASE("TEST_PROC_DECODE", "[PROCESSOR]"){
    CHIP8::Proc proc{};
    CHIP8::Proc::INSTRUCTION instru = proc.decode(0xffff);
    const auto [opcode, x, y, z] = instru.getData();
    REQUIRE( opcode == 0xf );
    REQUIRE( x == 0xf );
    REQUIRE( y == 0xf );
    REQUIRE( z == 0xf );
    REQUIRE( x == instru.getX());
    REQUIRE( y == instru.getY());
    REQUIRE( z == instru.getNible());
    REQUIRE( instru.getAddr() == 0xfff);
    REQUIRE( instru.getByte() == 0xff);

    instru = proc.decode(0xabcd);
    const auto [opcode2, x2, y2, z2] = instru.getData();
    REQUIRE( opcode2 == 10 );
    REQUIRE( x2 == 11 );
    REQUIRE( y2 == 12 );
    REQUIRE( z2 == 13 );
    REQUIRE( opcode2 == instru.getOpCode());
    REQUIRE( x2 == instru.getX());
    REQUIRE( y2 == instru.getY());
    REQUIRE( z2 == instru.getNible());
    REQUIRE( instru.getAddr() == 0xbcd);
    REQUIRE( instru.getByte() == 0xcd);
}

TEST_CASE("TEST_PROC_EXECUTION", "[PROCESSOR]"){
    CHIP8::Proc proc{};
    const auto& display = proc.getDisplay();
    const auto& regV = proc.getAllVReg();
    const auto& regI = proc.getRegI();
    const auto& PC = proc.getPC();
    const auto& SP = proc.getSP();
    const auto& delayTimer = proc.getDelayReg();
    const auto& soundTimer = proc.getSoundReg();

    for(const auto reg : regV)
        REQUIRE(reg == 0);
    // const auto& memory = proc.getMemory();
    SECTION("Unknow COMMAND"){
        proc.execute(0xf9f9); //set register 0 at 0xff
        REQUIRE(regV.at(0) == 0x00);
    }
    SECTION("1nnn JP addr COMMAND"){
        const CHIP8::u16 addr = 0xfdfe;
        const CHIP8::u16 command = 0x1fff;
        const CHIP8::u16 value = command & addr;
        const CHIP8::u16 target = 0x0dfe; 
        proc.execute(value); 
        REQUIRE(PC == target);
    }
    SECTION("2nnn CALL addr COMMAND"){
        const CHIP8::u16 addr = 0xfdfe;
        const CHIP8::u16 command = 0x2fff;
        const CHIP8::u16 value = command & addr;
        const CHIP8::u16 target = 0x0dfe; 
        proc.execute(value); 
        REQUIRE(SP == 1);
        REQUIRE(PC == target);
    }
    SECTION("3xkk SE Vx, byte COMMAND"){
        const CHIP8::u16 x = 0xf1ff;
        const CHIP8::u16 command = 0x3f1E;
        const CHIP8::u16 value = command & x;
        proc.execute(0x611E);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x1E);
        REQUIRE(PC == 3);
    }
    SECTION("3xkk-2 SE Vx, byte COMMAND"){
        const CHIP8::u16 x = 0xf1ff;
        const CHIP8::u16 command = 0x3f1A;
        const CHIP8::u16 value = command & x;
        proc.execute(0x611E);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x1E);
        REQUIRE(PC == 2);
    }
    SECTION("4xkk SNE Vx, byte COMMAND"){
        const CHIP8::u16 x = 0xf1ff;
        const CHIP8::u16 command = 0x4f1E;
        const CHIP8::u16 value = command & x;
        proc.execute(0x611E);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x1E);
        REQUIRE(PC == 2);
    }
    SECTION("4xkk-2 SNE Vx, byte COMMAND"){
        const CHIP8::u16 x = 0xf1ff;
        const CHIP8::u16 command = 0x4f1A;
        const CHIP8::u16 value = command & x;
        proc.execute(0x611E);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x1E);
        REQUIRE(PC == 3);
    }
    SECTION("5xy0 SE Vx, Vy COMMAND"){
        const CHIP8::u16 command = 0x5010;
        const CHIP8::u16 value = command;
        proc.execute(0x611E);
        proc.execute(0x601E);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x1E);
        REQUIRE(regV.at(0) == 0x1E);
        REQUIRE(PC == 4);
    }
    SECTION("5xy0-2 SE Vx, Vy COMMAND"){
        const CHIP8::u16 command = 0x5010;
        const CHIP8::u16 value = command;
        proc.execute(0x611E);
        proc.execute(0x601F);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x1E);
        REQUIRE(regV.at(0) == 0x1F);
        REQUIRE(PC == 3);
    }
    SECTION("6xkk SET Vx COMMAND"){
        for(CHIP8::u16 i = 0; i < regV.size(); i++)
        {
            const CHIP8::u16 x = (i << 8) | 0xf0ff;
            const CHIP8::u16 byte = i | 0xff00;
            const CHIP8::u16 command = 0x6fff;
            const CHIP8::u16 value = command & x & byte;
            const CHIP8::u8 target = byte;
            // std::println("VALUE 6xkk: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, byte, command, value, target);
            proc.execute(value); //set register i at 0xf0
            REQUIRE(regV.at(i) == target);
        }
        SECTION("7xkk ADD Vx, KK COMMAND"){
            for(CHIP8::u16 i = 0; i < regV.size(); i++)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 byte = i | 0xff00;
                const CHIP8::u16 command = 0x7fff;
                const CHIP8::u16 value = command & x & byte;
                const CHIP8::u8 target = i + byte;
                // std::println("VALUE 7xkk: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, byte, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }

            SECTION("8xy0 LD Vx, Vy COMMAND"){
                for(CHIP8::u16 i = 0, j = regV.size()-1; i < regV.size() / 2; i++, j--)
                {
                    const CHIP8::u16 x = (i << 8) | 0xf0ff;
                    const CHIP8::u16 y = (j << 4) | 0xff0f;
                    const CHIP8::u16 command = 0x8ff0;
                    const CHIP8::u16 value = command & x & y;
                    // std::println("VALUE 8xy0: {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value);
                    proc.execute(value); //set register i at 0xff
                    REQUIRE(regV.at(i) == regV.at(j));
                }
            }
        }
        SECTION("8xy1 OR Vx, Vy COMMAND"){
            for(CHIP8::u16 i = 0, j = regV.size()-1; i < regV.size() / 2; i++, j--)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 y = (j << 4) | 0xff0f;
                const CHIP8::u16 command = 0x8ff1;
                const CHIP8::u16 value = command & x & y;
                const CHIP8::u8 target = i | j;
                // std::println("VALUE 8xy1: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }
        }
        SECTION("8xy2 AND Vx, Vy COMMAND"){
            for(CHIP8::u16 i = 0, j = regV.size()-1; i < regV.size() / 2; i++, j--)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 y = (j << 4) | 0xff0f;
                const CHIP8::u16 command = 0x8ff2;
                const CHIP8::u16 value = command & x & y;
                const CHIP8::u8 target = i & j;
                // std::println("VALUE 8xy2: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }
        }
        SECTION("8xy3 XOR Vx, Vy COMMAND"){
            for(CHIP8::u16 i = 0, j = regV.size()-1; i < regV.size() / 2; i++, j--)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 y = (j << 4) | 0xff0f;
                const CHIP8::u16 command = 0x8ff3;
                const CHIP8::u16 value = command & x & y;
                const CHIP8::u8 target = i ^ j;
                // std::println("VALUE 8xy3: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }
        }
        SECTION("8xy4 ADD Vx, Vy COMMAND"){
            for(CHIP8::u16 i = 0, j = regV.size()-1; i < regV.size() / 2; i++, j--)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 y = (j << 4) | 0xff0f;
                const CHIP8::u16 command = 0x8ff4;
                const CHIP8::u16 value = command & x & y;
                const CHIP8::u8 target = i + j;
                // std::println("VALUE 8xy4: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }
        }
        SECTION("8xy5 SUB Vx, Vy COMMAND"){
            for(CHIP8::u16 i = 0, j = regV.size()-1; i < regV.size() / 2; i++, j--)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 y = (j << 4) | 0xff0f;
                const CHIP8::u16 command = 0x8ff5;
                const CHIP8::u16 value = command & x & y;
                const CHIP8::u8 target = i - j;
                // std::println("VALUE 8xy5: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }
        }
        SECTION("8xy6 SHR Vx COMMAND"){
            for(CHIP8::u16 i = 0; i < regV.size() - 1; i++)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 y = 0xff0f;
                const CHIP8::u16 command = 0x8ff6;
                const CHIP8::u16 value = command & x & y;
                const CHIP8::u8 target = i >> 1;
                // std::println("VALUE 8xy6: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }
        }
        SECTION("8xy7 SUBN Vx, Vy COMMAND"){
            for(CHIP8::u16 i = 0, j = regV.size()-1; i < regV.size() / 2; i++, j--)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 y = (j << 4) | 0xff0f;
                const CHIP8::u16 command = 0x8ff7;
                const CHIP8::u16 value = command & x & y;
                const CHIP8::u8 target = j - i;
                // std::println("VALUE 8xy7: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }
        }
        SECTION("8xyE SHL Vx COMMAND"){
            for(CHIP8::u16 i = 0; i < regV.size() - 1; i++)
            {
                const CHIP8::u16 x = (i << 8) | 0xf0ff;
                const CHIP8::u16 y = 0xff0f;
                const CHIP8::u16 command = 0x8ffE;
                const CHIP8::u16 value = command & x & y;
                const CHIP8::u8 target = i << 1;
                // std::println("VALUE 8xyE: {:#06b} {:#06b} {:#06b} {:#06b} {:#06b}", x, y, command, value, target);
                proc.execute(value); //set register i at 0xff
                REQUIRE(regV.at(i) == target);
            }
        }
    }
    SECTION("9xy0 SNE Vx, Vy COMMAND"){
        const CHIP8::u16 command = 0x9010;
        const CHIP8::u16 value = command;
        proc.execute(0x611E);
        proc.execute(0x601E);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x1E);
        REQUIRE(regV.at(0) == 0x1E);
        REQUIRE(PC == 3);
    }
    SECTION("9xy0-2 SNE Vx, Vy COMMAND"){
        const CHIP8::u16 command = 0x9010;
        const CHIP8::u16 value = command;
        proc.execute(0x611E);
        proc.execute(0x601F);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x1E);
        REQUIRE(regV.at(0) == 0x1F);
        REQUIRE(PC == 4);
    }
    SECTION("Annn LD I, addr COMMAND"){
        const CHIP8::u16 addr = 0xfdfe;
        const CHIP8::u16 command = 0xAfff;
        const CHIP8::u16 value = command & addr;
        const CHIP8::u16 target = 0x0dfe; 
        proc.execute(value); 
        REQUIRE(regI == target);
    }
    SECTION("Bnnn JP V0, addr COMMAND"){
        const CHIP8::u16 addr = 0xfdfe;
        const CHIP8::u16 command = 0xBfff;
        const CHIP8::u16 value = command & addr;
        const CHIP8::u16 target = 0x0dff; 
        proc.execute(0x6001);
        proc.execute(value);
        REQUIRE(PC == target);
    }
    SECTION("Fx07 LD Vx, DT COMMAND"){
        const CHIP8::u16 x = 0xf0ff;
        const CHIP8::u16 command = 0xff07;
        const CHIP8::u16 value = command & x;
        proc.execute(0x6069);
        proc.execute(value);
        REQUIRE(regV.at(0) == delayTimer);
    }
    SECTION("Fx15 LD DT, Vx COMMAND"){
        const CHIP8::u16 x = 0xf0ff;
        const CHIP8::u16 command = 0xff15;
        const CHIP8::u16 value = command & x;
        const CHIP8::u8 target = 0x69; 
        proc.execute(0x6069);
        proc.execute(value);
        REQUIRE(regV.at(0) == 0x69);
        REQUIRE(delayTimer == target);
    }
    SECTION("Fx18 LD DT, Vx COMMAND"){
        const CHIP8::u16 x = 0xf1ff;
        const CHIP8::u16 command = 0xff18;
        const CHIP8::u16 value = command & x;
        const CHIP8::u8 target = 0x69; 
        proc.execute(0x6169);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x69);
        REQUIRE(soundTimer == target);
    }
    SECTION("Fx1E LD DT, Vx COMMAND"){
        const CHIP8::u16 x = 0xf1ff;
        const CHIP8::u16 command = 0xff1E;
        const CHIP8::u16 value = command & x;
        const CHIP8::u8 target = 0x69; 
        proc.execute(0x6169);
        proc.execute(value);
        REQUIRE(regV.at(1) == 0x69);
        REQUIRE(regI == target);
    }
    SECTION("CLS COMMAND"){
        proc.execute(0x00E0);
        for(const auto& data : display)
        {
            REQUIRE(data == 0);
        }
    }

}

TEST_CASE("TEST_PROC_KEYBOARD", "[PROCESSOR]"){
    CHIP8::Proc proc{};
    const auto& isKeyPressed = proc.isKeyPressed();
    const auto& keyPressed = proc.getKeyPressed();
    const auto& PC = proc.getPC();
    const auto& regV = proc.getAllVReg();
    // const auto& display = proc.getDisplay();
    // const auto& regI = proc.getRegI();
    // const auto& SP = proc.getSP();
    // const auto& delayTimer = proc.getDelayReg();
    // const auto& soundTimer = proc.getSoundReg();
    SECTION("Ex9E SKP Vx COMMAND"){
        proc.execute(0x6E01);
        REQUIRE(isKeyPressed == false);
        REQUIRE(keyPressed == 0x0);
        proc.setKeyPressed(0x02);
        REQUIRE(isKeyPressed == true);
        REQUIRE(keyPressed == 0x02);
        proc.execute(0xEE9E);
        REQUIRE(PC == 3);
    }
    SECTION("Ex9E-2 SKP Vx COMMAND"){
        proc.execute(0x6E01);
        proc.setKeyPressed(0x01);
        REQUIRE(isKeyPressed == true);
        REQUIRE(keyPressed == 0x01);
        proc.execute(0xEE9E);
        REQUIRE(PC == 2);
    }
    SECTION("ExA1 SKP Vx COMMAND"){
        proc.execute(0x6E01);
        REQUIRE(isKeyPressed == false);
        REQUIRE(keyPressed == 0x0);
        proc.setKeyPressed(0x02);
        REQUIRE(isKeyPressed == true);
        REQUIRE(keyPressed == 0x02);
        proc.execute(0xEEA1);
        REQUIRE(PC == 2);
    }
    SECTION("ExA1-2 SKP Vx COMMAND"){
        proc.execute(0x6E01);
        proc.setKeyPressed(0x01);
        REQUIRE(isKeyPressed == true);
        REQUIRE(keyPressed == 0x01);
        proc.execute(0xEEA1);
        REQUIRE(PC == 3);
    }
    SECTION("Fx0A LD Vx, k COMMAND"){
        proc.execute(0x6001);
        proc.setKeyPressed(0x01);
        REQUIRE(isKeyPressed == true);
        REQUIRE(keyPressed == 0x01);
        proc.execute(0xF00A);
        REQUIRE(PC == 2);
        REQUIRE(regV.at(0) == 0x01);
    }
    SECTION("Fx0A LD Vx, k COMMAND"){
        proc.execute(0x6001);
        REQUIRE(isKeyPressed == false);
        REQUIRE(keyPressed == 0x00);
        proc.execute(0xF00A);
        REQUIRE(PC == 1);
    }
}

TEST_CASE("TEST_PROC_DISPLAY", "[PROCESSOR]"){
    CHIP8::Proc proc{};
    // const auto& display = proc.getDisplay();
    // const auto& regV = proc.getAllVReg();
    // const auto& regI = proc.getRegI();
    // const auto& PC = proc.getPC();
    // const auto& SP = proc.getSP();
    // const auto& delayTimer = proc.getDelayReg();
    // const auto& soundTimer = proc.getSoundReg();
    SECTION("CLS COMMAND"){
        proc.execute(0x00E0);
    }
}

TEST_CASE("TEST_PROC_MEMORY", "[PROCESSOR]"){
    CHIP8::Proc proc{};
    const auto& memory = proc.getMemory();
    const auto& regV = proc.getAllVReg();
    const auto& regI = proc.getRegI();
    // const auto& PC = proc.getPC();
    // const auto& SP = proc.getSP();
    // const auto& delayTimer = proc.getDelayReg();
    // const auto& soundTimer = proc.getSoundReg();
    for(const auto data : memory)
        REQUIRE(data == 0x00);

    SECTION("Fx33 LD B, Vx COMMAND"){
        proc.execute(0x60FF);
        REQUIRE(regI == 0);
        proc.execute(0xF033);
        REQUIRE(memory.at(0) == 2);
        REQUIRE(memory.at(1) == 5);
        REQUIRE(memory.at(2) == 5);
    }
    SECTION("Fx55 LD B, Vx COMMAND"){
        //store data
        proc.execute(0x60FF);
        proc.execute(0x61FF);
        proc.execute(0x62FF);
        proc.execute(0x63FF);
        proc.execute(0x64FF);
        proc.execute(0x65FF);
        proc.execute(0x66FF);
        proc.execute(0x67FF);
        proc.execute(0x68FF);
        proc.execute(0x69FF);
        proc.execute(0x6AFF);
        proc.execute(0x6BFF);
        proc.execute(0x6CFF);
        proc.execute(0x6DFF);
        proc.execute(0x6EFF);
        REQUIRE(regI == 0);
        proc.execute(0xFE55);
        for(size_t i = 0; i < 15; i++)
            REQUIRE(memory.at(i) == 0xff);
    }
    SECTION("Fx65 LD B, Vx COMMAND"){
        //store data
        proc.execute(0x60FF);
        proc.execute(0x61FF);
        proc.execute(0x62FF);
        proc.execute(0x63FF);
        proc.execute(0x64FF);
        proc.execute(0x65FF);
        proc.execute(0x66FF);
        proc.execute(0x67FF);
        proc.execute(0x68FF);
        proc.execute(0x69FF);
        proc.execute(0x6AFF);
        proc.execute(0x6BFF);
        proc.execute(0x6CFF);
        proc.execute(0x6DFF);
        proc.execute(0x6EFF);
        REQUIRE(regI == 0);
        for(size_t i = 0; i < 15; i++)
            REQUIRE(regV.at(i) == 0xff);
        proc.execute(0xFE65);
        for(size_t i = 0; i < 15; i++)
            REQUIRE(regV.at(i) == 0x00);
    }
}