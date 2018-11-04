//
// Created by daniel on 02/11/18.
//
// A dialog box window. Must be in an ncurses program!
// Creates a window which contains the dialog box.
//

#ifndef CMDPAGES_PAGE_H
#define CMDPAGES_PAGE_H

#include <ncurses.h>

class Page {
public:
    void display();
    void destroy();
    Page();
private:
    WINDOW *window;
    //TODO Add content
    void create_newwin(int height, int width, int starty, int startx);
};

#include "Page.cpp"

#endif //CMDPAGES_PAGE_H
