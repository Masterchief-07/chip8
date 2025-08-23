#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include "chip8/proc.hpp"

TEST_CASE("TEST_PROC_DECODE", "[PROCESSOR]"){
    CHIP8::Proc proc{};
    const auto [opcode, x, y, z] = proc.decode(0xffff).getData();
    REQUIRE( opcode == 15 );
    REQUIRE( x == 15 );
    REQUIRE( y == 15 );
    REQUIRE( z == 15 );

    const auto [opcode2, x2, y2, z2] = proc.decode(0xabcd).getData();
    REQUIRE( opcode2 == 10 );
    REQUIRE( x2 == 11 );
    REQUIRE( y2 == 12 );
    REQUIRE( z2 == 13 );
}

TEST_CASE("TEST_PROC_EXECUTION", "[PROCESSOR]"){
    CHIP8::Proc proc{};
    const auto& display = proc.getDisplay();
    // const auto& memory = proc.getMemory();

    SECTION("CLS COMMAND"){
        proc.execute(0x00E0);
        for(const auto& data : display)
        {
            REQUIRE(data == 0);
        }
    }

}