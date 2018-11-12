//
// Created by daniel on 06/11/18.
//

#include "MenuBox.h"
#include <string>

MenuBox::MenuBox(int x, int y) : Box::Box(x, y) {

}

MenuBox::MenuBox(int x, int y, std::vector<std::string> entries) : Box::Box(x, y) {
    menuEntries = entries;

}

void MenuBox::display() {
    //std::string entriesArray[3] = *menuEntries;
    mvwprintw(window,2,4,"Size of options array: %d",menuEntries.size());
    mvwprintw(window,3,4,"Menu 1: %s",menuEntries[0].c_str());
    Box::display();

//    for (int i = 0; i < sizeof(*menuEntries); ++i) {
//        char entries[][] = *menuEntries;
//        mvwprintw(window,2,i,entries[i]);
//    }
}

void MenuBox::addMenuEntry(std::string text) {

}
