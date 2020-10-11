//
// Created by daniel on 06/11/18.
//

#ifndef CMDPAGES_MENUBOX_H
#define CMDPAGES_MENUBOX_H

#include "Box.h"
#include "ContainerPage.h"
#include "MenuEntry.h"
#include <string>
#include <vector>
#include <map>

/** A Box which contains MenuEntries which can be selected to go to its defined page.
 *
 */
class MenuBox : public Box {
public:
    static MenuBox* makeMenuBox(const std::vector<std::string>& entries);
    static MenuBox* makeMenuBox(std::vector<MenuEntry> entries);
    MenuBox(int x,int y, std::vector<MenuEntry> entries);
    void display() override;
    int getSelected() const;
    ContainerPage* getDestinationPage();
    void setDestinationPage(int entryNumber, ContainerPage *pagePointer);
    void setDestinationPageByName(const std::string &name, ContainerPage *pagePointer);
    void moveSelectionDown();
    void moveSelectionUp();
private:
    MenuEntry* getEntryWithName(const std::string& name) const;
    std::string menuName = "Menu";
    std::vector<MenuEntry> menuEntries;
    int selectedEntry;
};

#endif //CMDPAGES_MENUBOX_H
