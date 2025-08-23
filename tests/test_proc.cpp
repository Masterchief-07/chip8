#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include "chip8/proc.hpp"

TEST_CASE("TEST_PROC_INIT", "[PROCESSOR]"){
    CHIP8::Proc proc{};
    const auto [opcode, x, y, z] = proc.decode(0xffff);
    REQUIRE( opcode == 15 );
    REQUIRE( x == 15 );
    REQUIRE( y == 15 );
    REQUIRE( z == 15 );

    const auto [opcode2, x2, y2, z2] = proc.decode(0xabcd);
    REQUIRE( opcode2 == 10 );
    REQUIRE( x2 == 11 );
    REQUIRE( y2 == 12 );
    REQUIRE( z2 == 13 );
}