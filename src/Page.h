//
// Created by daniel on 02/11/18.
//
// A dialog box contentWindow. Must be in an ncurses program!
// Creates a contentWindow which contains the dialog box.
//

#ifndef CMDPAGES_PAGE_H
#define CMDPAGES_PAGE_H

#include <functional>
#include <curses.h>
#include <array>
using namespace std::placeholders;

/** An empty page.
 * This object contains Box's which draw a set background onto the terminal, implement this class to add functionality.
 * It has the variable previousPage to be used to know which page to show when this one is closed
 */
class Page {
public:
    typedef std::function<void(Page*)> PageCallback;

    Page();

    int input{};
    virtual void iterate(const PageCallback &changePageCallback);

    virtual void display();
    virtual void updateSize();
    virtual void destroy();
    void createWindows(int width, int height);

//    void setColours(Colour background, Colour foreground, Colour highlightedBackground, Colour highlightedForeground);

    Page* getPreviousPage();
    void setPreviousPage(Page* prevPage);

    enum event
    {   EnterKey = 0,
        EscapeKey = 1,
        UpKey = 2,
        DownKey = 3
    };
    virtual void triggerEvent(Page::event eventType);


protected:
    int windowWidth;
    int windowHeight;
    WINDOW* contentWindow;
    WINDOW* backgroundWindow;

    std::array<int,4> calculateCoordinates();

    Page* previousPage{};
    std::string pageName;

};

#endif //CMDPAGES_PAGE_H
