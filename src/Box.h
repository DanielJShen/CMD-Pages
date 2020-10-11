//
// Created by daniel on 04/11/18.
//

#ifndef CMDPAGES_BOX_H
#define CMDPAGES_BOX_H

#include <curses.h>

/** A box is a displayed window which is displayed in the center of the terminal.
 *  Extend the class to display something inside the box. Designed to be places inside a ContainerPage
 */
class Box {
public:
    virtual void display();
    WINDOW *window;
    WINDOW *borderWindow;
    Box(int x,int y);
private:
    void createBox(int height, int width);
};

#endif //CMDPAGES_BOX_H
