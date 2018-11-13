#include <utility>

//
// Created by daniel on 06/11/18.
//

#include "MenuBox.h"
#include <string>

MenuBox::MenuBox(int x, int y) : Box::Box(x, y) {

}

MenuBox::MenuBox(int x, int y, std::vector<std::string> entries) : Box::Box(x, y) {
    menuEntries = std::move(entries);
    selectedEntry = 0;
}

MenuBox::MenuBox(int width, std::vector<std::string> entries) : Box::Box(width, (int) entries.size()+4) {
    menuEntries = std::move(entries);
    selectedEntry = 0;
}

void MenuBox::display() {
    mvwprintw(window,0,2,"%s",menuName.c_str());
    for (int i = 0; i < menuEntries.size(); ++i) {
        std::string value = menuEntries[i];

        int position;
        std::string offset;
        if( value.size()%2 == 0 ) {
            position = static_cast<int>( (window->_maxx - value.size())/2 );
            offset = "  ";
        } else {
            position = static_cast<int>( (window->_maxx - value.size() + 1)/2 );
            offset = " ";
        }

        if(selectedEntry == i){
            wattron(window,COLOR_PAIR(1));
        }
        mvwprintw(window,i+2, position, "[ %s%s]", value.c_str(), offset.c_str());
        wattroff(window,COLOR_PAIR(1));
    }
    Box::display();
}

void MenuBox::setSelected(int position) {
    if(position >= menuEntries.size()){
        return;
    }
    if(position < 0){
        if(position == -1){
            position += menuEntries.size();
        }else{
            return;
        }
    }
    selectedEntry = position;
}
int MenuBox::getSelected() {
    return selectedEntry;
}

ContainerPage* MenuBox::getSelectionPage() {
    if( menuEntryContents.count(selectedEntry) == 0 ) {
        throw std::runtime_error("There is no page defined for the selected entry");
    }
    return menuEntryContents[selectedEntry];
}
void MenuBox::setEntryPage(int entryNumber, ContainerPage* pagePointer) {
    if(entryNumber >= menuEntries.size() || entryNumber < 0){
        return;
    }
    menuEntryContents.insert(std::pair<int, ContainerPage*>(entryNumber, pagePointer));
}

void MenuBox::addMenuEntry(std::string text) {

}
