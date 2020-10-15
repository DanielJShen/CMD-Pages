//
// Created by Daniel on 11/10/2020.
//

#include <string>
#include <utility>
#include "MenuEntry.h"
#include "Logger.h"

MenuEntry::MenuEntry(std::string name, PageWithBox* containerPage) {
    this->entryText = std::move(name);
    this->pagePointer = containerPage;
}

MenuEntry::MenuEntry(std::string& name) {
    this->entryText = std::move(name);
    this->pagePointer = nullptr;
}

void MenuEntry::setDestinationPage(PageWithBox *containerPage) {
    Logger::appendMessage("Setting destination page to: "+std::to_string((long)containerPage));
    this->pagePointer = containerPage;
}

std::string MenuEntry::getName() const {
    return this->entryText;
}

PageWithBox* MenuEntry::getDestinationPage() {
    return this->pagePointer;
}
