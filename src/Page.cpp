//
// Created by daniel on 02/11/18.
//

#include "Page.h"
#include "ContainerPage.h"
#include "MenuBox.h"
#include <ncurses.h>

Page::Page() {
    int height = LINES;
    int width = COLS;
    #define COLOR_GRAY 9
    init_color(COLOR_GRAY,400,400,400);
    init_color(COLOR_BLUE,0,0,800);
    init_pair(0,COLOR_BLUE,COLOR_BLACK);

    create_newwin(height, width, 0, 0);

}
void Page::display( void ) {
    redrawwin(window);
    wrefresh(window);

}
void Page::destroy( void ) {
    delwin(window);
}

void Page::create_newwin(int height, int width, int starty, int startx) {
    window = newwin(height, width, starty, startx);
    //box(window, 0 , 0);
    wbkgd(window,COLOR_PAIR(0));
}

Page* Page::getPreviousPage() {
    return previousPage;
}

void Page::setPreviousPage(Page* prevPage) {
    previousPage = prevPage;
}

