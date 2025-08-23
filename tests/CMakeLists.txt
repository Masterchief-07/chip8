add_subdirectory(${CMAKE_SOURCE_DIR}/externals/catch2  /externals/catch2 EXCLUDE_FROM_ALL)

add_executable(tests test_main.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain chip8_lib)

include(CTest)
include(${CMAKE_SOURCE_DIR}/externals/catch2/extras/Catch.cmake)
catch_discover_tests(tests)