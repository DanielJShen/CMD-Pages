//
// Created by daniel on 04/11/18.
//

#include "Box.h"

Box::Box(int x, int y) {
    #define COLOR_GRAY 9
    #define COLOR_DARKGRAY 10
    window = nullptr;
    borderWindow = nullptr;

    init_color(COLOR_GRAY,400,400,400);
    init_color(COLOR_DARKGRAY,440,440,440);
    init_color(COLOR_BLUE,0,0,800);
    init_pair(1,COLOR_BLUE,COLOR_GRAY);
    init_pair(2,COLOR_DARKGRAY,COLOR_BLUE);
    init_pair(3,COLOR_BLUE,COLOR_DARKGRAY);
    #define BOX_COLOUR_PAIR 3
    createBox(x,y);

}

void Box::display() {
    redrawwin(borderWindow);
    redrawwin(window);
    wrefresh(borderWindow);
    wrefresh(window);
}

void Box::createBox(int width, int height) {
    int startY = (LINES - height) / 2;
    int startX = (COLS - width) / 2;

    borderWindow = newwin(height, width+2, startY, startX - 1);
    wbkgd(borderWindow,COLOR_PAIR(BOX_COLOUR_PAIR));

    window = newwin(height, width, startY, startX);
    box(window, 0 , 0);
    wbkgd(window,COLOR_PAIR(BOX_COLOUR_PAIR));
}