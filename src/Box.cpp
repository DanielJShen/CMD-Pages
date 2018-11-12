//
// Created by daniel on 04/11/18.
//

#include "Box.h"

Box::Box(int x, int y) {

    #define COLOR_GRAY 0
    init_color(COLOR_GRAY,400,400,400);
    init_pair(1,COLOR_CYAN,COLOR_GRAY);
    init_pair(2,COLOR_BLACK,COLOR_CYAN);
    createBox(x,y);

}

void Box::display() {
    wrefresh(window);
}

void Box::createBox(int width, int height) {
    int starty = (LINES - height)/2;
    int startx = (COLS - width)/2;
    window = newwin(height, width, starty, startx);
    box(window, 0 , 0);
    wbkgd(window,COLOR_PAIR(1));
}