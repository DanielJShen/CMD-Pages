//
// Created by daniel on 02/11/18.
//

#include "Page.h"
#include "Logger.h"
#include "UUIDGenerator.h"
#include "BlockingInputProcessor.h"

#include <utility>

#define COLOR_GRAY 9
#define COLOR_DARKGRAY 10

#define BOX_HIGHLIGHT_COLOUR_PAIR 1
#define BOX_COLOUR_PAIR 2
#define BKG_COLOUR_PAIR 3

bool Page::useGlobalColours = FALSE;

Page::Page(std::string name, std::array<int, 2> windowSize, IInputProcessor& inputProcessor) : m_inputProcessor(inputProcessor) {
    pageUUID = UUIDGenerator::generateUUID();
    Logger::appendMessage("Creating page: " + name + "   UUID: "+std::to_string(pageUUID));
    pageName = std::move(name);
    previousPage = nullptr;
    backgroundWindow = nullptr;
    contentWindow = nullptr;
    windowWidth = windowSize[0];
    windowHeight = windowSize[1];

    init_color(COLOR_GRAY,400,400,400);
    init_color(COLOR_DARKGRAY,220,220,220);

    colour_background1 = COLOR_WHITE;
    colour_background2 = COLOR_BLACK;
    colour_box1 = COLOR_WHITE;
    colour_box2 = COLOR_DARKGRAY;
    colour_boxHighlighted1 = COLOR_WHITE;
    colour_boxHighlighted2 = COLOR_GRAY;


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
    IInputProcessor::inputEvent eventToBeTriggered = m_inputProcessor.readInput();
    if (eventToBeTriggered != IInputProcessor::NoAction) {
        triggerEvent(changePageCallback, eventToBeTriggered);
    }
}

Page* Page::getPreviousPage() {
    return previousPage;
}

void Page::setPreviousPage(Page* prevPage) {
    previousPage = prevPage;
}

void Page::triggerEvent(const PageCallback &changePageCallback, IInputProcessor::inputEvent eventType) {
    if (eventType == IInputProcessor::EscapeKey) {
            changePageCallback(nullptr);
    }
}

void Page::display() {
    if (!useGlobalColours) {
        init_pair(3,colour_background1,colour_background2);    //BKG_COLOUR_PAIR
        init_pair(2,colour_box1,colour_box2); //BOX_COLOUR_PAIR
        init_pair(1,colour_boxHighlighted1,colour_boxHighlighted2);     //BOX_HIGHLIGHT_COLOUR_PAIR
    }

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

void Page::setColours(short background1, short background2, short box1, short box2, short boxHighlighted1,
                      short boxHighlighted2) {
    colour_background1 = background1;
    colour_background2 = background2;
    colour_box1 = box1;
    colour_box2 = box2;
    colour_boxHighlighted1 = boxHighlighted1;
    colour_boxHighlighted2 = boxHighlighted2;

    init_pair(3,colour_background1,colour_background2);    //BKG_COLOUR_PAIR
    init_pair(2,colour_box1,colour_box2); //BOX_COLOUR_PAIR
    init_pair(1,colour_boxHighlighted1,colour_boxHighlighted2);     //BOX_HIGHLIGHT_COLOUR_PAIR
}

bool Page::getUseGlobalColours() {
    return useGlobalColours;
}

void Page::setUseGlobalColours(bool val) {
    useGlobalColours = val;
}
