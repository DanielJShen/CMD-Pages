//
// Created by daniel on 04/11/18.
//

#ifndef CMDPAGES_BOX_H
#define CMDPAGES_BOX_H

#include <curses.h>
#include <array>
#include <functional>
#include "Page.h"
#include "PagesCore.h"

/** A box is a displayed window which is displayed in the center of the terminal.
 *  Extend the class to display something inside the box. Designed to be places inside a PageWithBox
 */
class Box {
public:
    virtual void display();
    WINDOW *window;
    WINDOW *borderWindow;
    Box(int x,int y);
    void updateSize();

    enum event
    {   EnterKey = 0,
        EscapeKey = 1,
        UpKey = 2,
        DownKey = 3
    };
    virtual void triggerEvent(Box::event eventType, const std::function<void(PagesCore::*)(Page*)> &changePageCallback);

private:
    void createBox();
    std::array<int,4> calculateCoordinates();
    std::array<int,4> calculateBorderCoordinates();
    int width;
    int height;

protected:
    std::string boxName = "Box";
};

#endif //CMDPAGES_BOX_H
