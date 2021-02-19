//
// Created by Daniel on 18/02/2021.
//

#include <curses.h>
#include "BlockingInputProcessor.h"

IInputProcessor::inputEvent BlockingInputProcessor::readInput() {
    notimeout(stdscr, TRUE);
    int input = wgetch(stdscr);
    if (input == 27) { // 27 is the escape code
        nodelay(stdscr, TRUE);
        wgetch(stdscr); //Skips the '[' character
        input = wgetch(stdscr);
        nodelay(stdscr, FALSE);
        if (input == ERR) {
            return IInputProcessor::EscapeKey;
        }
    }
    if (input == 'A') {
        return IInputProcessor::UpKey;
    } else if (input == 'B' ) {
        return IInputProcessor::DownKey;
    } else if (input == 'C') {
        return IInputProcessor::RightKey;
    } else if (input == 'D') {
        return IInputProcessor::LeftKey;
    } else if (input == 10) {
        return IInputProcessor::EnterKey;
    } else if (input == KEY_RESIZE) {
        return IInputProcessor::Resize;
    } else {
        return IInputProcessor::NoAction;
    }
}


IInputProcessor& UseBlockingInputProcessor() {
    static std::unique_ptr<IInputProcessor> instance = std::make_unique<BlockingInputProcessor>();
    return *instance;
}