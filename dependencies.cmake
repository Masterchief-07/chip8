include(cmake/CPM.cmake)

CPMAddPackage(
    URI "gh:raysan5/raylib#5.5"
    OPTIONS "BUILD_EXAMPLES OFF"
)

CPMAddPackage(
    URI "gh:catchorg/catch2#v3.11.0"
    OPTIONS "BUILD_EXAMPLES OFF"
)

if(BUILD_TUI)
    CPMAddPackage(
        URI "gh:ArthurSonzogni/FTXUI#v6.1.9"
    )
endif()