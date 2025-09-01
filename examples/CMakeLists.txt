add_executable(game game.cpp)
target_link_libraries(game PRIVATE chip8_lib)
file(GLOB CHIP8GAMES ${CMAKE_SOURCE_DIR}/externals/chip8_roms/*.ch8)
message(DEBUG "allgames: ${CHIP8GAMES}")

# file(COPY ${CMAKE_SOURCE_DIR}/externals/chip8_roms/games.)