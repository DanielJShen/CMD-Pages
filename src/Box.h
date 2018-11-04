//
// Created by daniel on 04/11/18.
//
// A Box goes inside a Page and contains the functionality of the page
//

#ifndef CMDPAGES_BOX_H
#define CMDPAGES_BOX_H

#include <ncurses.h>

class Box {
public:
    void display();
    Box(int x,int y);
private:
    WINDOW *window;
    void create_newwin(int height, int width, int starty, int startx);
};


#endif //CMDPAGES_BOX_H
