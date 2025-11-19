//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef INPUT_HANDLER_UNIX_H
#define INPUT_HANDLER_UNIX_H

#include <termios.h>
#include <unistd.h>

#include <atomic>

#include "input_event.h"

void setNonCanonicalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void resetTerminalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);  // Enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

InputEvent getKeyPress() {
    fd_set readfds;
    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000;  // Poll every 10 ms

    int result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (result > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
        char ch;
        if (read(STDIN_FILENO, &ch, 1) == 1) {
            switch (ch) {
            case 27:
                return InputEvent::ESCAPE;
            case ' ':
                return InputEvent::SPACE;
            case 'a':
            case 'A':
                return InputEvent::KEY_A;
            }
        }
    }
    return InputEvent::NONE;
}

void MoveCursorToEnd() {
    std::cout << "\033[999;999H" << std::flush;  // Move cursor to a far location
}

#endif  // INPUT_HANDLER_UNIX_H
