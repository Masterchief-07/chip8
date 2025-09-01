file(GLOB_RECURSE CHIP8GAMES ${CMAKE_SOURCE_DIR}/externals/chip8_roms/games/*.ch8)
file(COPY ${CHIP8GAMES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(game game.cpp)
target_link_libraries(game PRIVATE chip8_lib)