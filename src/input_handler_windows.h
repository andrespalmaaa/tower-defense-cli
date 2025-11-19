//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef INPUT_HANDLER_WINDOWS_H
#define INPUT_HANDLER_WINDOWS_H

#include <conio.h>

#include <atomic>
#include <thread>

#include "input_event.h"

InputEvent getKeyPress() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
        case 27:  // Escape key
            return InputEvent::ESCAPE;
        case ' ':
            return InputEvent::SPACE;
        case 'a':
        case 'A':
            return InputEvent::KEY_A;
        }
    }

    return InputEvent::NONE;
}



#endif  // INPUT_HANDLER_WINDOWS_H
