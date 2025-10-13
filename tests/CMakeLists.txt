enable_testing()
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

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
