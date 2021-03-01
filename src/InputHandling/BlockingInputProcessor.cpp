//
// Created by Daniel on 18/02/2021.
//

#include <curses.h>
#include "BlockingInputProcessor.h"

KeyInput BlockingInputProcessor::readInput() {
    notimeout(stdscr, TRUE);
    int input = wgetch(stdscr);
    if (input == 27) { // 27 is the escape code
        nodelay(stdscr, TRUE);
        wgetch(stdscr); //Skips the '[' character
        input = wgetch(stdscr);
        nodelay(stdscr, FALSE);
        if (input == ERR) {
            return KeyInput(KeyInput::inputEvent::EscapeKey);
        }
        Logger::appendMessage("Function Key Input:"+std::to_string(input));

        if (input == 'A') {
            return KeyInput(KeyInput::inputEvent::UpKey);
        } else if (input == 'B' ) {
            return KeyInput(KeyInput::inputEvent::DownKey);
        } else if (input == 'C') {
            return KeyInput(KeyInput::inputEvent::RightKey);
        } else if (input == 'D') {
            return KeyInput(KeyInput::inputEvent::LeftKey);
        } else if (input == 53) {
            return KeyInput(KeyInput::inputEvent::PageUp);
        } else if (input == 54) {
            return KeyInput(KeyInput::inputEvent::PageDown);
        } else if (input == 72) {
            return KeyInput(KeyInput::inputEvent::HomeKey);
        } else if (input == 70) {
            return KeyInput(KeyInput::inputEvent::EndKey);
        }
    }
    Logger::appendMessage("Key Input:"+std::to_string(input));
    if (input == KEY_RESIZE) {
        return KeyInput(KeyInput::inputEvent::Resize);
    } else if (input == 10) {
        return KeyInput(KeyInput::inputEvent::EnterKey);
    } else {
        return KeyInput(KeyInput::inputEvent::NoAction);
    }
}


IInputProcessor& UseBlockingInputProcessor() {
    static std::unique_ptr<IInputProcessor> instance = std::make_unique<BlockingInputProcessor>();
    return *instance;
}