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
 * @param changePageCallback A callback for changing which page will be iterated over.
 */
void MenuPage::iterate(const PageCallback &changePageCallback) {
    Page::event eventToBeTriggered = processInput();
    if (eventToBeTriggered != Page::NoAction) {
        triggerEvent(changePageCallback, eventToBeTriggered);
    }
}

void MenuPage::display() {
    //mvwprintw(contentWindow,0,2,"%s",pageName.c_str());
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
            wattron(contentWindow, COLOR_PAIR(BOX_HIGHLIGHT_COLOUR_PAIR));
        }
        mvwprintw(contentWindow, i + 2, textPosition, "[ %s%s]", value.c_str(), offset.c_str());
        wattroff(contentWindow, COLOR_PAIR(BOX_HIGHLIGHT_COLOUR_PAIR));
    }
    Page::display();
}

void MenuPage::updateSize() {
    Page::updateSize();
}

void MenuPage::destroy() {
    Page::destroy();
}

/** Triggers an event on the Page
 *
 * @param eventType The event being triggered
 * @param changePageCallback A callback for changing the currently displayed page
 */
void MenuPage::triggerEvent(const PageCallback &changePageCallback, Page::event eventType) {
    switch (eventType) {
        case UpKey:
            if (!menuEntries.empty()) {
                int newSelectedEntry = selectedEntry - 1;
                if(newSelectedEntry < 0){
                    newSelectedEntry = (int)menuEntries.size() - 1;
                }
                selectedEntry = newSelectedEntry;
            }
            display();
            break;
        case DownKey:
            if (!menuEntries.empty()) {
                int newSelectedEntry = selectedEntry + 1;
                if(newSelectedEntry >= menuEntries.size()){
                    newSelectedEntry = 0;
                }
                selectedEntry = newSelectedEntry;
            }
            display();
            break;
        case Resize:
            updateSize();
            display();
            break;
        case EscapeKey:
            changePageCallback(nullptr);
            break;
        case EnterKey:
            Page* destinationPage = getDestinationPage();
            if (destinationPage != nullptr) {
                changePageCallback(destinationPage);
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
        return nullptr;
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
