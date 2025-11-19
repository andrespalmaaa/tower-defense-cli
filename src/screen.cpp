//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "screen.h"

#include <iostream>

void Screen::SetCursor(int x, int y) { std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H"; }

void Screen::RenderText(int x, int y, std::string text) {
    SetCursor(x, y);
    std::cout << text;
    std::cout.flush();
}

void Screen::MoveCursorToEnd() {
    std::cout << "\033[999;999H" << std::flush;  // Move cursor to a far location
}
