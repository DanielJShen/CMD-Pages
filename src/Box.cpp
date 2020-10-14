//
// Created by daniel on 04/11/18.
//

#include "Box.h"
#include "Logger.h"

Box::Box(int x, int y) {
    #define COLOR_GRAY 9
    #define COLOR_DARKGRAY 10
    window = nullptr;
    borderWindow = nullptr;
    width = x;
    height = y;

    init_color(COLOR_GRAY,400,400,400);
    init_color(COLOR_DARKGRAY,170,170,170);
    init_color(COLOR_BLUE,0,0,800);
    init_pair(1,COLOR_WHITE,COLOR_GRAY);
    init_pair(2,COLOR_WHITE,COLOR_DARKGRAY);
    #define BOX_HIGHLIGHT_COLOUR_PAIR 1
    #define BOX_COLOUR_PAIR 2
    createBox();

}

void Box::display() {
    redrawwin(borderWindow);
    redrawwin(window);
    wrefresh(borderWindow);
    wrefresh(window);
}

void Box::updateSize() {
    auto [height, width, startY, startX] = calculateCoordinates();
    mvwin(window,startY,startX);
//    wresize(window, height, width);
    auto [borderHeight, borderWidth, borderStartY, borderStartX] = calculateBorderCoordinates();
    mvwin(borderWindow,borderStartY,borderStartX);
//    wresize(borderWindow, borderHeight, borderWidth);
}

void Box::createBox() {
    auto [borderHeight, borderWidth, borderStartY, borderStartX] = calculateBorderCoordinates();
    borderWindow = newwin(borderHeight, borderWidth, borderStartX, borderStartY);
    wbkgd(borderWindow,COLOR_PAIR(BOX_COLOUR_PAIR));

    auto [height, width, startY, startX] = calculateCoordinates();
    window = newwin(height, width, startY, startX);
    box(window, 0 , 0);
    wbkgd(window,COLOR_PAIR(BOX_COLOUR_PAIR));
}

std::array<int, 4> Box::calculateBorderCoordinates() {
    int startY = (LINES - height) / 2;
    int startX = (COLS - width) / 2;
    return {height, width+2, startY, startX - 1};
}
std::array<int, 4> Box::calculateCoordinates() {
    int startY = (LINES - height) / 2;
    int startX = (COLS - width) / 2;
    return {height, width, startY, startX};
}