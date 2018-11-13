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
    virtual void display();
    WINDOW *window;
    WINDOW *borderWindow;
    Box(int x,int y);
private:
    void createBox(int height, int width);
};

//#include "Box.cpp"

#endif //CMDPAGES_BOX_H
