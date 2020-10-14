//
// Created by daniel on 02/11/18.
//
// A dialog box window. Must be in an ncurses program!
// Creates a window which contains the dialog box.
//

#ifndef CMDPAGES_PAGE_H
#define CMDPAGES_PAGE_H

#include <curses.h>

/** An empty page.
 * This page covers the terminal in a set colour, implement this class and draw on top of this blank page.
 * It has the variable previousPage to know which page to show when this one is closed
 */
class Page {
public:
    virtual void display();
    void destroy();

    virtual void updateSize();
    Page();
    Page* getPreviousPage();
    void setPreviousPage(Page* prevPage);
private:
    WINDOW* window;
    void create_newwin(int height, int width, int starty, int startx);
    Page* previousPage;
};

#endif //CMDPAGES_PAGE_H
