#pragma once
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>

namespace CHIP8_TUI
{
enum class ScreenState : uint8_t
{
    HOME = 0,
    GAME,
    EDITOR,
};

class Tui
{
    public:
        Tui();
        ~Tui();
        void displayHomeScreen();
        void selectGameScreen();
        void displayGameScreen();
        void displayEditorScreen();
    
    private:
        ftxui::Screen _mScreen;
        ftxui::Element _mHomeElements;
        ftxui::Element _mGameElements;
        ftxui::Element _mEditorElements;

};

}