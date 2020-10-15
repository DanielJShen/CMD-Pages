//
// Created by daniel on 06/11/18.
//

#ifndef CMDPAGES_MENUBOX_H
#define CMDPAGES_MENUBOX_H

#include "Box.h"
#include "PageWithBox.h"
#include "MenuEntry.h"
#include <string>
#include <vector>
#include <map>

/** A Box which contains MenuEntries which can be selected to go to its defined page.
 *
 */
class MenuBox : public Box {
public:
    static MenuBox* makeMenuBox(std::string name, const std::vector<std::string>& entries);
    static MenuBox* makeMenuBox(std::string name, std::vector<MenuEntry> entries);
    MenuBox(int x,int y, std::string name, std::vector<MenuEntry> entries);
    void display() override;
    void setDestinationPage(int entryNumber, PageWithBox *pagePointer);
    void setDestinationPageByName(const std::string &name, PageWithBox *pagePointer);
    void triggerEvent(Box::event eventType, const std::function<void(PagesCore::*)(Page*)> &changePageCallback) override;
private:
    MenuEntry* getEntryWithName(const std::string& name) const;
    PageWithBox* getDestinationPage();
    int getSelected() const;
    std::string boxName = "Menu";
    std::vector<MenuEntry> menuEntries;
    int selectedEntry;
};

#endif //CMDPAGES_MENUBOX_H
