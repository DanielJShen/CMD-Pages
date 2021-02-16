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
    init_pair(1,COLOR_WHITE,COLOR_GRAY);     //BOX_HIGHLIGHT_COLOUR_PAIR
    init_pair(2,COLOR_WHITE,COLOR_DARKGRAY); //BOX_COLOUR_PAIR
    init_pair(3,COLOR_WHITE,COLOR_BLACK);    //BKG_COLOUR_PAIR

    init_pair(4,COLOR_BLUE,COLOR_GRAY);      //BOX_HIGHLIGHT_DIRECTORY_COLOUR_PAIR
    init_pair(5,COLOR_BLUE,COLOR_DARKGRAY);  //BOX_DIRECTORY_COLOUR_PAIR
    init_pair(6,COLOR_GREEN,COLOR_GRAY);     //BOX_HIGHLIGHT_EXECUTABLE_COLOUR_PAIR
    init_pair(7,COLOR_GREEN,COLOR_DARKGRAY); //BOX_EXECUTABLE_COLOUR_PAIR
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

void Page::triggerEvent(const PageCallback &changePageCallback, Page::event eventType) {

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

Page::event Page::processInput() {
    //input = wgetch(contentWindow);
    //if(input == 27) { // 27 = Esc code

        //Code block is equivalent to keypad mode in getch but with a shorter wait when pressing ESC

    //keypad(contentWindow, TRUE);
    notimeout(contentWindow, TRUE);
//        nodelay(contentWindow, TRUE);
//        intrflush(contentWindow, FALSE);
//        int count = 0;
//        //Gets the input and sleeps if the input is empty
//        do {
//            input = wgetch(contentWindow);
//            count++;
//            if(input == ERR) {
//              usleep(10);
//            }
//        } while(input == ERR && count < 100);
        input = wgetch(contentWindow);
        Logger::appendMessage("Input INT: "+std::to_string(input));
        if (input == 27) {
            nodelay(contentWindow, TRUE);
            int input2 = wgetch(contentWindow);
            Logger::appendMessage("Input2 INT: "+std::to_string(input2));
            input = wgetch(contentWindow);
            Logger::appendMessage("Input3 INT: "+std::to_string(input));
            nodelay(contentWindow, FALSE);
            if (input == ERR) {
                Logger::appendMessage("Input: Escape");
                return Page::EscapeKey;
            }
        }

        if (input == 'A') {
            Logger::appendMessage("Input: KEY_UP");
            return Page::UpKey;
        } else if (input == 'B' ) {
            Logger::appendMessage("Input: KEY_DOWN");
            return Page::DownKey;
        } else if (input == 'C') {
            Logger::appendMessage("Input: KEY_RIGHT");
            return Page::RightKey;
        } else if (input == 'D') {
            Logger::appendMessage("Input: KEY_LEFT");
            return Page::LeftKey;
        } else if (input == 10) { //Enter
            Logger::appendMessage("Input: KEY_ENTER");
            return Page::EnterKey;
        } else if (input == KEY_RESIZE) {
            Logger::appendMessage("Input: KEY_RESIZE");
            return Page::Resize;
        } else {
            return Page::NoAction;
        }
    return Page::NoAction;
}