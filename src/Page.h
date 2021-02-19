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
#include <memory>
#include "IInputProcessor.h"
using namespace std::placeholders;

/** An empty NCurses window of variable size with a solid background, it can be extended to add functionality.
 * The class is responsible for displaying a box and a background as well as storing a pointer to the previous page,
 * so that the page at the pointer can be used when this one is closed.
 */
class Page {
public:
    typedef std::function<void(Page*)> PageCallback;

    Page(std::string name, std::array<int, 2> windowSize, IInputProcessor& inputProcessor);

    virtual void iterate(const PageCallback &changePageCallback);

    virtual void display();
    virtual void updateSize();
    virtual void destroy();


    std::string getName();
//    void setColours(Colour background, Colour foreground, Colour highlightedBackground, Colour highlightedForeground);

    Page* getPreviousPage();
    void setPreviousPage(Page* prevPage);


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

    IInputProcessor& m_inputProcessor;
    virtual void triggerEvent(const PageCallback &changePageCallback, IInputProcessor::inputEvent eventType);

};

#endif //CMDPAGES_PAGE_H
