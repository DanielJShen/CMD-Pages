//
// Created by Daniel on 11/10/2020.
//

#include <string>
#include <utility>
#include "MenuEntry.h"
#include "Logger.h"

MenuEntry::MenuEntry(std::string name, Page* containerPage) {
    this->entryName = std::move(name);
    this->pagePointer = containerPage;
}

MenuEntry::MenuEntry(std::string& name) {
    this->entryName = std::move(name);
    this->pagePointer = nullptr;
}

void MenuEntry::setDestinationPage(Page *containerPage) {
    Logger::appendMessage("Setting destination page of '"+this->entryName+"' to: "+std::to_string((long)containerPage));
    this->pagePointer = containerPage;
}

void MenuEntry::setName(std::string& name) {
    this->entryName = name;
}

std::string MenuEntry::getName() {
    return this->entryName;
}

Page* MenuEntry::getDestinationPage() {
    return this->pagePointer;
}
