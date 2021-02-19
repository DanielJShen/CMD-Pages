//
// Created by daniel on 06/11/18.
//

#include <utility>
#include "MenuPage.h"
#include "Logger.h"
#include <string>
#include <cmath>
#include <unistd.h>

#define COLOR_GRAY 9
#define COLOR_DARKGRAY 10

#define BOX_HIGHLIGHT_COLOUR_PAIR 1
#define BOX_COLOUR_PAIR 2

MenuPage::MenuPage(std::string name, std::vector<Page*> pages, IInputProcessor& inputProcessor) : Page(name,calculateWindowDimensions(name,pages),inputProcessor) {
    pageName = std::move(name);
    availablePages = std::move(pages);
    selectedEntry = 0;
}

std::array<int, 2> MenuPage::calculateWindowDimensions(const std::string& name, const std::vector<Page*>& pages) {
    int width = (int) getLargestPageNameLength(name,pages)+15;
    int height = (int) pages.size()+4;
    return {width, height};
}

int MenuPage::getLargestPageNameLength(const std::string& name, const std::vector<Page*>& pages) {
    int highestLength = (int) name.length();
    for (auto & page : pages) {
        int entryLength = page->getName().length();
        if ( entryLength > highestLength) {
            highestLength = entryLength;
        }
    }
    return highestLength;
}

void MenuPage::display() {
    for (int i = 0; i < availablePages.size(); i++) {
        std::string value = availablePages[i]->getName();

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

/** Triggers an inputEvent on the Page
 *
 * @param eventType The inputEvent being triggered
 * @param changePageCallback A callback for changing the currently displayed page
 */
void MenuPage::triggerEvent(const PageCallback &changePageCallback, IInputProcessor::inputEvent eventType) {
    switch (eventType) {
        case IInputProcessor::UpKey:
            if (!availablePages.empty()) {
                int newSelectedEntry = selectedEntry - 1;
                if(newSelectedEntry < 0){
                    newSelectedEntry = (int)availablePages.size() - 1;
                }
                selectedEntry = newSelectedEntry;
            }
            display();
            break;
        case IInputProcessor::DownKey:
            if (!availablePages.empty()) {
                int newSelectedEntry = selectedEntry + 1;
                if(newSelectedEntry >= availablePages.size()){
                    newSelectedEntry = 0;
                }
                selectedEntry = newSelectedEntry;
            }
            display();
            break;
        case IInputProcessor::Resize:
            updateSize();
            display();
            break;
        case IInputProcessor::EscapeKey:
            changePageCallback(nullptr);
            break;
        case IInputProcessor::EnterKey:
            Page* destinationPage = getPagePointerForSelectedMenuEntry();
            if (destinationPage != nullptr) {
                changePageCallback(destinationPage);
            }
            break;
    }
}

Page *MenuPage::getPageWithName(const std::string& name) {
    for (auto & page : availablePages) {
        if (page->getName() == name) {
            return const_cast<Page *>(page);
        }
    }
    throw std::exception();
}

Page* MenuPage::getPagePointerForSelectedMenuEntry() {
    if(availablePages[selectedEntry] == nullptr ) {
        Logger::appendMessage("There is no destination page defined for the selected entry.");
        return nullptr;
    }
    return availablePages[selectedEntry];
}

int MenuPage::getSelected() {
    return selectedEntry;
}
