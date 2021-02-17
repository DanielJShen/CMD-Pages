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

    Page(std::string name, std::array<int, 2> windowSize);

    int input{};
    virtual void iterate(const PageCallback &changePageCallback);

    virtual void display();
    virtual void updateSize();
    virtual void destroy();


    std::string getName();
//    void setColours(Colour background, Colour foreground, Colour highlightedBackground, Colour highlightedForeground);

    Page* getPreviousPage();
    void setPreviousPage(Page* prevPage);

    enum event
    {   NoAction = 0,
        EnterKey = 1,
        EscapeKey = 2,
        UpKey = 3,
        DownKey = 4,
        LeftKey = 5,
        RightKey = 6,
        Resize = 7
    };


protected:
    int windowWidth;
    int windowHeight;
    WINDOW* contentWindow;
    WINDOW* backgroundWindow;

    std::array<int,4> calculateCoordinates();
    void createWindows(int width, int height);

    Page* previousPage{};
    int pageUUID;
    std::string pageName;

    Page::event processInput();
    virtual void triggerEvent(const PageCallback &changePageCallback, Page::event eventType);

};

#endif //CMDPAGES_PAGE_H
