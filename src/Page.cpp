//
// Created by daniel on 02/11/18.
//

#include "Page.h"
#include <ncurses.h>

Page::Page() {
    int height = LINES;
    int width = COLS;
    #define COLOR_GRAY 0
    init_color(COLOR_GRAY,400,400,400);
    init_pair(1,COLOR_CYAN,COLOR_GRAY);

    printf("Creating Page...");
    create_newwin(height, width, 0, 0);

}
void Page::display( void ) {
    wrefresh(window);

}
void Page::destroy( void ) {
    delwin(window);
}

void Page::create_newwin(int height, int width, int starty, int startx) {
    window = newwin(height, width, starty, startx);
    //box(window, 0 , 0);
    wbkgd(window,COLOR_PAIR(1));
}