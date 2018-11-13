//
// Created by daniel on 04/11/18.
//

#include "Box.h"

Box::Box(int x, int y) {

    #define COLOR_GRAY 9
    #define COLOR_DARKGRAY 10
    init_color(COLOR_GRAY,400,400,400);
    init_color(COLOR_DARKGRAY,440,440,440);
    init_color(COLOR_BLUE,0,0,800);
    init_pair(1,COLOR_BLUE,COLOR_GRAY);
    init_pair(2,COLOR_DARKGRAY,COLOR_BLUE);
    init_pair(3,COLOR_BLUE,COLOR_DARKGRAY);
    createBox(x,y);

}

void Box::display() {
    wrefresh(borderWindow);
    wrefresh(window);
}

void Box::createBox(int width, int height) {
    int starty = (LINES - height)/2;
    int startx = (COLS - width)/2;

    borderWindow = newwin(height, width+2, starty, startx-1);
    wbkgd(borderWindow,COLOR_PAIR(3));

    window = newwin(height, width, starty, startx);
    box(window, 0 , 0);
    wbkgd(window,COLOR_PAIR(3));
}