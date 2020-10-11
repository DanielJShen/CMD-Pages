//
// Created by daniel on 06/11/18.
//

#include <utility>
#include "MenuBox.h"
#include "MenuEntry.h"
#include "Logger.h"
#include <string>
#include <etip.h>


MenuBox *MenuBox::makeMenuBox(const std::vector<std::string>& entries) {
    int highestLength = 0;
    for (auto & entry : entries) {
        int entryLength = entry.length();
        if ( entryLength > highestLength) {
            highestLength = entryLength;
        }
    }
    int width = (int) highestLength+15;
    int height = (int) entries.size()+4;

    std::vector<MenuEntry> menuEntries = {};
    menuEntries.reserve(entries.size());
    for (std::string entry : entries) {
        menuEntries.emplace_back( MenuEntry(entry) );
    }

    return new MenuBox(width,height,menuEntries);
}

MenuBox::MenuBox(int width, int height, std::vector<MenuEntry> entries) : Box::Box(width, height) {
    menuEntries = std::move(entries);
    selectedEntry = 0;
}

void MenuBox::display() {
    mvwprintw(window,0,2,"%s",menuName.c_str());
    for (int i = 0; i < menuEntries.size(); ++i) {
        std::string value = menuEntries[i].getName();

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

void MenuBox::moveSelectionUp() {
    if (menuEntries.empty()) {
        return;
    }

    int newSelectedEntry = selectedEntry - 1;
    if(newSelectedEntry < 0){
        newSelectedEntry = (int)menuEntries.size() - 1;
    }
    selectedEntry = newSelectedEntry;
}
void MenuBox::moveSelectionDown() {
    if (menuEntries.empty()) {
        return;
    }

    int newSelectedEntry = selectedEntry + 1;
    if(newSelectedEntry >= menuEntries.size()){
        newSelectedEntry = 0;
    }
    selectedEntry = newSelectedEntry;
}

MenuEntry *MenuBox::getEntryWithName(const std::string& name) const {
    for (const auto & menuEntry : menuEntries) {
        if (menuEntry.getName() == name) {
            return const_cast<MenuEntry *>(&menuEntry);
        }
    }
    throw std::exception();
}

ContainerPage* MenuBox::getDestinationPage() {
    if(menuEntries[selectedEntry].getDestinationPage() == nullptr ) {
        Logger::appendMessage("There is no destination page defined for the selected entry");
        throw std::runtime_error("");
    }
    return menuEntries[selectedEntry].getDestinationPage();
}
void MenuBox::setDestinationPage(int entryNumber, ContainerPage* pagePointer) {
    if(entryNumber >= menuEntries.size() || entryNumber < 0){
        return;
    }
    menuEntries[entryNumber].setDestinationPage(pagePointer);
}
void MenuBox::setDestinationPageByName(const std::string& name, ContainerPage* pagePointer) {
    MenuEntry* entry = getEntryWithName(name);
    entry->setDestinationPage(pagePointer);
}

int MenuBox::getSelected() const {
    return selectedEntry;
}
