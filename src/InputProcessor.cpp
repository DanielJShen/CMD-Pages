//
// Created by Daniel on 18/02/2021.
//

#include <curses.h>
#include "InputProcessor.h"
/** This method uses wgetch to read key inputs, its a blocking method wand will wait until there is an input.
 *
 * @return InputProcessor::inputEvent An event representing the key pressed.
 */
InputProcessor::inputEvent InputProcessor::processInput() {
    notimeout(stdscr, TRUE);
    int input = wgetch(stdscr);
    if (input == 27) { // 27 is the escape code
        nodelay(stdscr, TRUE);
        wgetch(stdscr); //Skips the '[' character
        input = wgetch(stdscr);
        nodelay(stdscr, FALSE);
        if (input == ERR) {
            return InputProcessor::EscapeKey;
        }
    }
    if (input == 'A') {
        return InputProcessor::UpKey;
    } else if (input == 'B' ) {
        return InputProcessor::DownKey;
    } else if (input == 'C') {
        return InputProcessor::RightKey;
    } else if (input == 'D') {
        return InputProcessor::LeftKey;
    } else if (input == 10) {
        return InputProcessor::EnterKey;
    } else if (input == KEY_RESIZE) {
        return InputProcessor::Resize;
    } else {
        return InputProcessor::NoAction;
    }
}