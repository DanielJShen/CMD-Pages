//
// Created by Daniel on 27/02/2021.
//

#include <vector>
#include "TextboxInputProcessor.h"
#include "curses.h"

KeyInput TextboxInputProcessor::readInput() {
    notimeout(stdscr, TRUE);
    int input = wgetch(stdscr);
    if (input == 27) { // 27 is the escape code
        nodelay(stdscr, TRUE);
        wgetch(stdscr); //Skips the '[' character
        input = wgetch(stdscr);
        nodelay(stdscr, FALSE);
        if (input == ERR) {
            return KeyInput(KeyInput::inputEvent::EscapeKey);
        } else if (input == 'A') {
            return KeyInput(KeyInput::inputEvent::UpKey);
        } else if (input == 'B' ) {
            return KeyInput(KeyInput::inputEvent::DownKey);
        } else if (input == 'C') {
            return KeyInput(KeyInput::inputEvent::RightKey);
        } else if (input == 'D') {
            return KeyInput(KeyInput::inputEvent::LeftKey);
        } else if (input == 10) {
            return KeyInput(KeyInput::inputEvent::EnterKey);
        }
    }
    //std::string validCharacters = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890!\"£$%^&*()-=_+[]{};:'@#~,<.>/?\\|`¬";

    if (input == KEY_RESIZE) {
        return KeyInput(KeyInput::inputEvent::Resize);
    } else if (isascii(input)) {
        return KeyInput((char) input);
    }

    return KeyInput(KeyInput::inputEvent::NoAction);
}