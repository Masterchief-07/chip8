cmake_minimum_required(VERSION 3.31)

PROJECT(chip8_lib LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# add_subdirectory(${CMAKE_SOURCE_DIR}/externals/raylib)
include(dependencies.cmake)

add_library(${PROJECT_NAME}
                    ${CMAKE_SOURCE_DIR}/src/chip8.cpp
                    ${CMAKE_SOURCE_DIR}/src/display.cpp
                    ${CMAKE_SOURCE_DIR}/src/program.cpp
                    ${CMAKE_SOURCE_DIR}/src/keyboard.cpp
                    ${CMAKE_SOURCE_DIR}/src/proc.cpp
            )  
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

add_definitions("-Wall" "-Wpedantic" "-Werror")

add_subdirectory(${CMAKE_SOURCE_DIR}/examples)

include(CTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)