//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef SCREEN_H
#define SCREEN_H

#include <string>

// A class to manage the console screen output.
//
// This class provides methods to move the cursor to a specific position on the
// screen, to render a string at a specific position on the screen and to move
// the cursor to the end of the screen.
class Screen {
   public:
    static void SetCursor(int x, int y);
    static void RenderText(int x, int y, std::string text);
    static void MoveCursorToEnd();
};

#endif  // SCREEN_H