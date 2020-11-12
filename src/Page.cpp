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

Page::Page() {
    pageName = "Box";
    previousPage = nullptr;
    window = nullptr;
    borderWindow = nullptr;
    windowWidth = 0;
    windowHeight = 0;

    init_color(COLOR_GRAY,400,400,400);
    init_color(COLOR_DARKGRAY,170,170,170);
    init_color(COLOR_BLUE,0,0,800);
    init_pair(1,COLOR_WHITE,COLOR_GRAY);
    init_pair(2,COLOR_WHITE,COLOR_DARKGRAY);
}

/** Creates the Curses windows, this is required in order to display anything.
 *
 * @param width Width of the displayed window
 * @param height Height of the displayed window
 */
void Page::createWindows(int width, int height) {

    windowWidth = width;
    windowHeight = height;

    auto [winHeight, winWidth, startY, startX] = calculateCoordinates();
    window = newwin(winHeight, winWidth, startY, startX);
    box(window, 0 , 0);
    wbkgd(window,COLOR_PAIR(BOX_COLOUR_PAIR));

    auto [borderWindowHeight, borderWindowWidth, borderStartY, borderStartX] = calculateBorderCoordinates();
    borderWindow = newwin(borderWindowHeight, borderWindowWidth, borderStartX, borderStartY);
    wbkgd(borderWindow,COLOR_PAIR(BOX_COLOUR_PAIR));
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
    mvwprintw(window,0,2,"%s",pageName.c_str());
    redrawwin(window);
    redrawwin(borderWindow);
    wrefresh(window);
    wrefresh(borderWindow);
}

void Page::updateSize() {
    auto [height, width, startY, startX] = calculateCoordinates();
    mvwin(window,startY,startX);
    wresize(window, windowHeight, windowWidth);

    auto [borderHeight, borderWidth, borderStartY, borderStartX] = calculateBorderCoordinates();
    mvwin(borderWindow,borderStartY,borderStartX);
    wresize(borderWindow, borderHeight, borderWidth);

}

void Page::destroy() {
    delwin(borderWindow);
    delwin(window);
}

std::array<int, 4> Page::calculateCoordinates() {
    int startY = (LINES - windowHeight) / 2;
    int startX = (COLS - windowWidth) / 2;
    return {windowHeight, windowWidth, startY, startX};
}

std::array<int, 4> Page::calculateBorderCoordinates() {
    int startY = (LINES - windowHeight) / 2;
    int startX = (COLS - windowWidth) / 2;
    return {windowHeight, windowWidth + 2, startY, startX - 1};
}
