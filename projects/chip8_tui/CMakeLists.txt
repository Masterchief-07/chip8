
add_executable(
        CHIP8_TUI 
        main.cpp
)

target_include_directories(CHIP8_TUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(CHIP8_TUI 
                                PRIVATE 
                                chip8_lib 
                                ftxui::screen
                                ftxui::component
                                ftxui::dom        
                        )