//
// Created by daniel on 02/11/18.
//

#include "Page.h"
#include "Logger.h"
#include "UUIDGenerator.h"
#include <unistd.h>

#include <utility>

#define COLOR_GRAY 9
#define COLOR_DARKGRAY 10

#define BOX_HIGHLIGHT_COLOUR_PAIR 1
#define BOX_COLOUR_PAIR 2
#define BKG_COLOUR_PAIR 3

Page::Page(std::string name, std::array<int, 2> windowSize) {
    pageUUID = UUIDGenerator::generateUUID();
    pageName = std::move(name);
    previousPage = nullptr;
    backgroundWindow = nullptr;
    contentWindow = nullptr;
    windowWidth = windowSize[0];
    windowHeight = windowSize[1];

    init_color(COLOR_GRAY,400,400,400);
    init_color(COLOR_DARKGRAY,170,170,170);
    init_color(COLOR_BLUE,0,0,800);
    init_pair(1,COLOR_WHITE,COLOR_GRAY);     //BOX_HIGHLIGHT_COLOUR_PAIR
    init_pair(2,COLOR_WHITE,COLOR_DARKGRAY); //BOX_COLOUR_PAIR
    init_pair(3,COLOR_WHITE,COLOR_BLACK);    //BKG_COLOUR_PAIR

    init_pair(4,COLOR_BLUE,COLOR_GRAY);      //BOX_HIGHLIGHT_DIRECTORY_COLOUR_PAIR
    init_pair(5,COLOR_BLUE,COLOR_DARKGRAY);  //BOX_DIRECTORY_COLOUR_PAIR
    init_pair(6,COLOR_GREEN,COLOR_GRAY);     //BOX_HIGHLIGHT_EXECUTABLE_COLOUR_PAIR
    init_pair(7,COLOR_GREEN,COLOR_DARKGRAY); //BOX_EXECUTABLE_COLOUR_PAIR

    createWindows(windowWidth, windowHeight);
}

std::string Page::getName() {
    return pageName;
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
    InputProcessor::inputEvent eventToBeTriggered = InputProcessor::processInput();
    if (eventToBeTriggered != InputProcessor::NoAction) {
        triggerEvent(changePageCallback, eventToBeTriggered);
    }
}

Page* Page::getPreviousPage() {
    return previousPage;
}

void Page::setPreviousPage(Page* prevPage) {
    previousPage = prevPage;
}

void Page::triggerEvent(const PageCallback &changePageCallback, InputProcessor::inputEvent eventType) {
    if (eventType == InputProcessor::EscapeKey) {
            changePageCallback(nullptr);
    }
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
