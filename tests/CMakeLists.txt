enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/externals/catch2  ${CMAKE_BINARY_DIR}/externals/catch2 EXCLUDE_FROM_ALL)
include(${CMAKE_SOURCE_DIR}/externals/catch2/extras/Catch.cmake)

add_executable(UnitTests 
                ${CMAKE_SOURCE_DIR}/tests/test_main.cpp
                ${CMAKE_SOURCE_DIR}/tests/test_display.cpp
                ${CMAKE_SOURCE_DIR}/tests/test_keyboard.cpp
                ${CMAKE_SOURCE_DIR}/tests/test_proc.cpp
                ${CMAKE_SOURCE_DIR}/tests/test_program.cpp
            )
target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain chip8_lib)

# catch_discover_tests(tests)
catch_discover_tests(
  UnitTests
  TEST_PREFIX
  "unittests."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "unittests."
  OUTPUT_SUFFIX
  .xml)
