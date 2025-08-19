cmake_minimum_required(VERSION 3.31)

PROJECT(chip8 LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/externals/raylib)

add_executable(${PROJECT_NAME}  
                    ${CMAKE_SOURCE_DIR}/main.cpp
                    ${CMAKE_SOURCE_DIR}/src/chip8.cpp
                    ${CMAKE_SOURCE_DIR}/src/display.cpp
                )

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

add_definitions("-Wall" "-Wpedantic" "-Werror")