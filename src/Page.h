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

    /** Sets the colours to use for this page or for every page if useGlobalColours(TRUE) is called. The foreground colour is the colour of text. <br><br>
     * To use custom colours, use init_color from ncurses,
     * e.g. init_color(COLOR_DARKGRAY,170,170,170);
     *
     * @param background1 Foreground colour of the window used as the background of the page
     *               <br> Default: COLOR_WHITE
     * @param background2 Background colour of the window used as the background of the page
     *               <br> Default: COLOR_BLACK
     * @param box1 Foreground colour of the window used for functionality (box in the center of the terminal)
     *               <br> Default: COLOR_WHITE
     * @param box2 Background colour of the window used for functionality (box in the center of the terminal)
     *               <br> Default: COLOR_DARKGRAY
     * @param boxHighlighted1 Foreground colour of highlighted text in the window used for functionality (box in the center of the terminal)
     *               <br> Default: COLOR_WHITE
     * @param boxHighlighted2 Background colour of highlighted text in the window used for functionality (box in the center of the terminal)
     *               <br> Default: COLOR_GRAY
     */
    void setColours(NCURSES_COLOR_T background1, NCURSES_COLOR_T background2, NCURSES_COLOR_T box1, NCURSES_COLOR_T box2, NCURSES_COLOR_T boxHighlighted1, NCURSES_COLOR_T boxHighlighted2);
    static void setUseGlobalColours(bool val);
    static bool getUseGlobalColours();

    Page* getPreviousPage();
    void setPreviousPage(Page* prevPage);


protected:
    int windowWidth;
    int windowHeight;
    WINDOW* contentWindow;
    WINDOW* backgroundWindow;

    NCURSES_COLOR_T colour_background1;
    NCURSES_COLOR_T colour_background2;
    NCURSES_COLOR_T colour_box1;
    NCURSES_COLOR_T colour_box2;
    NCURSES_COLOR_T colour_boxHighlighted1;
    NCURSES_COLOR_T colour_boxHighlighted2;

    static bool useGlobalColours;

    std::array<int,4> calculateCoordinates();
    void createWindows(int width, int height);

    Page* previousPage{};
    int pageUUID;
    std::string pageName;

    IInputProcessor& m_inputProcessor;

    /** Triggers an inputEvent on the Page
    *
    * @param eventType The inputEvent being triggered
    * @param changePageCallback A callback for changing the currently displayed page
    */
    virtual void triggerEvent(const PageCallback &changePageCallback, IInputProcessor::inputEvent eventType);

};

#endif //CMDPAGES_PAGE_H
