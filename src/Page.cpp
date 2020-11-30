//
// Created by daniel on 02/11/18.
//

#include "Page.h"
#include "Logger.h"
#include <unistd.h>

#define COLOR_GRAY 9
#define COLOR_DARKGRAY 10

#define BOX_HIGHLIGHT_COLOUR_PAIR 1
#define BOX_COLOUR_PAIR 2
#define BKG_COLOUR_PAIR 3

Page::Page() {
    pageName = "Box";
    previousPage = nullptr;
    backgroundWindow = nullptr;
    contentWindow = nullptr;
    windowWidth = 0;
    windowHeight = 0;

    init_color(COLOR_GRAY,400,400,400);
    init_color(COLOR_DARKGRAY,170,170,170);
    init_color(COLOR_BLUE,0,0,800);
    init_pair(1,COLOR_WHITE,COLOR_GRAY);
    init_pair(2,COLOR_WHITE,COLOR_DARKGRAY);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
}

/** Creates the Curses windows, this is required in order to display anything.
 *
 * @param width Width of the displayed contentWindow
 * @param height Height of the displayed contentWindow
 */
void Page::createWindows(int width, int height) {

    windowWidth = width;
    windowHeight = height;

    backgroundWindow = newwin(LINES, COLS, 0, 0);
    wbkgd(backgroundWindow, COLOR_PAIR(BKG_COLOUR_PAIR));

    auto [winHeight, winWidth, startY, startX] = calculateCoordinates();
    contentWindow = newwin(winHeight, winWidth, startY, startX);
    box(contentWindow, 0 , 0);
    wbkgd(contentWindow, COLOR_PAIR(BOX_COLOUR_PAIR));
}

/** This function is run in a loop to detect key presses and update the terminal.
 *
 * @param changePageCallback A callback for changing the page to be iterated over.
 */
void Page::iterate(const PageCallback &changePageCallback) {
}

Page* Page::getPreviousPage() {
    return previousPage;
}

void Page::setPreviousPage(Page* prevPage) {
    previousPage = prevPage;
}

void Page::triggerEvent(Page::event eventType) {

}

void Page::display() {
    mvwprintw(contentWindow, 0, 2, "%s", pageName.c_str());
    redrawwin(backgroundWindow);
    redrawwin(contentWindow);
    wrefresh(backgroundWindow);
    wrefresh(contentWindow);
}

void Page::updateSize() {
    mvwin(backgroundWindow, 0, 0);
    wresize(backgroundWindow, LINES, COLS);

    auto [height, width, startY, startX] = calculateCoordinates();
    mvwin(contentWindow, startY, startX);
    wresize(contentWindow, windowHeight, windowWidth);

}

void Page::destroy() {
    delwin(backgroundWindow);
    delwin(contentWindow);
}

std::array<int, 4> Page::calculateCoordinates() {
    int startY = (LINES - windowHeight) / 2;
    int startX = (COLS - windowWidth) / 2;
    return {windowHeight, windowWidth, startY, startX};
}