//
// Created by daniel on 06/11/18.
//

#include <utility>
#include "MenuPage.h"
#include "MenuEntry.h"
#include "Logger.h"
#include <string>
#include <cmath>
#include <unistd.h>

#define COLOR_GRAY 9
#define COLOR_DARKGRAY 10

#define BOX_HIGHLIGHT_COLOUR_PAIR 1
#define BOX_COLOUR_PAIR 2

MenuPage::MenuPage(std::string name, const std::vector<std::string> &entries) : Page() {
    pageName = std::move(name);
    selectedEntry = 0;

    menuEntries.reserve(entries.size());
    for (std::string entry : entries) {
        menuEntries.emplace_back(MenuEntry(entry));
    }


    int width = (int) getLargestLength(menuEntries) + 15;
    int height = (int) menuEntries.size() + 4;
    createWindows(width, height);
}
MenuPage::MenuPage(std::string name, std::vector<MenuEntry> entries) : Page() {
    Logger::initLogger("CMDPages.log");
    pageName = std::move(name);
    menuEntries = std::move(entries);
    selectedEntry = 0;

    int width = (int) getLargestLength(menuEntries);+15;
    int height = (int) menuEntries.size()+4;
    createWindows(width, height);
}

int MenuPage::getLargestLength(std::vector<MenuEntry> entries) {
    int highestLength = 0;
    for (auto & entry : entries) {
        int entryLength = entry.getName().length();
        if ( entryLength > highestLength) {
            highestLength = entryLength;
        }
    }
    return highestLength;
}

/** This function is run in a loop to detect key presses and update the terminal.
 *
 * @param changePageCallback A callback for changing the page to be iterated over.
 */
void MenuPage::iterate(const PageCallback &changePageCallback) {
    input = wgetch(window);
    if(input == 27) { // 27 = Esc code

        //Code block is equivalent to keypad mode in getch but with a shorter wait when pressing ESC
        nodelay(window, true);
        int count = 0;
        do {
            input = wgetch(window);//Gets the [ character from escape codes or ERR when ESC is pressed
            count++;
            usleep(10);
        } while(input == ERR && count < 100);
        input = wgetch(window);
        nodelay(window, false);

        if (input == 'A') { // \033[A = Up
            triggerEvent(Page::UpKey);
        } else if (input == 'B') { // \033[B = Down
            triggerEvent(Page::DownKey);
        } else if (input == ERR) { // No input or Escape
            changePageCallback(nullptr);
            return;
        }

    } else if (input == 10) { // 10 = Enter
        changePageCallback(getDestinationPage());
        return;
    } else if (input == KEY_RESIZE) {
        updateSize();
    } else {
        return;
    }
    display();
}

void MenuPage::display() {
    Page::display();
    //mvwprintw(window,0,2,"%s",pageName.c_str());
    for (int i = 0; i < menuEntries.size(); ++i) {
        std::string value = menuEntries[i].getName();

        double widthAvailable = windowWidth - 1;
        int textPosition;
        std::string offset;
        if( value.size()%2 == 0 ) {
            double textLength = (double)value.size() + 5;
            textPosition = static_cast<int>( ceil((widthAvailable - textLength)/2) + 1 );
            offset = "  ";
        } else {
            double textLength = (double)value.size() + 4;
            textPosition = static_cast<int>( ceil((widthAvailable - textLength)/2) + 1 );
            offset = " ";
        }

        if(selectedEntry == i){
            wattron(window,COLOR_PAIR(BOX_HIGHLIGHT_COLOUR_PAIR));
        }
        mvwprintw(window,i+2, textPosition, "[ %s%s]", value.c_str(), offset.c_str());
        wattroff(window,COLOR_PAIR(BOX_HIGHLIGHT_COLOUR_PAIR));
    }
}

void MenuPage::updateSize() {
    Page::updateSize();
}

void MenuPage::destroy() {
    Page::destroy();
}

/** Triggers an event on the Box
 *
 * @param eventType The event being triggered
 * @param changePageCallback A callback for changing the currently displayed page
 */
void MenuPage::triggerEvent(Page::event eventType) {
    switch (eventType) {
        case UpKey:
            if (!menuEntries.empty()) {
                int newSelectedEntry = selectedEntry - 1;
                if(newSelectedEntry < 0){
                    newSelectedEntry = (int)menuEntries.size() - 1;
                }
                selectedEntry = newSelectedEntry;
            }
            break;
        case DownKey:
            if (!menuEntries.empty()) {
                int newSelectedEntry = selectedEntry + 1;
                if(newSelectedEntry >= menuEntries.size()){
                    newSelectedEntry = 0;
                }
                selectedEntry = newSelectedEntry;
            }
            break;
    }
}

MenuEntry *MenuPage::getEntryWithName(const std::string& name) {
    for (auto & menuEntry : menuEntries) {
        if (menuEntry.getName() == name) {
            return const_cast<MenuEntry *>(&menuEntry);
        }
    }
    throw std::exception();
}

Page* MenuPage::getDestinationPage() {
    if(menuEntries[selectedEntry].getDestinationPage() == nullptr ) {
        Logger::appendMessage("There is no destination page defined for the selected entry.");
        throw std::runtime_error("There is no destination page defined for the selected entry.");
    }
    return menuEntries[selectedEntry].getDestinationPage();
}
void MenuPage::setDestinationPage(int entryNumber, Page* pagePointer) {
    if(entryNumber >= menuEntries.size() || entryNumber < 0){
        return;
    }
    menuEntries[entryNumber].setDestinationPage(pagePointer);
}
void MenuPage::setDestinationPageByName(const std::string& name, Page* pagePointer) {
    MenuEntry* entry = getEntryWithName(name);
    entry->setDestinationPage(pagePointer);
}

int MenuPage::getSelected() const {
    return selectedEntry;
}
