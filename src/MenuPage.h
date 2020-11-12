//
// Created by daniel on 06/11/18.
//

#ifndef CMDPAGES_MENUPAGE_H
#define CMDPAGES_MENUPAGE_H

#include "Page.h"
#include "MenuEntry.h"
#include <string>
#include <vector>
#include <map>

/** A Page which contains a list of MenuEntries. One can be selected in order to go to the respective page.
 *
 */
class MenuPage : public Page {
public:
    MenuPage(std::string name, std::vector<MenuEntry> entries);
    MenuPage(std::string name, const std::vector<std::string>& entries);

    void iterate(const PageCallback &changePageCallback) override;

    void display() override;
    void updateSize() override;
    void destroy() override;

    void setDestinationPage(int entryNumber, Page *pagePointer);
    void setDestinationPageByName(const std::string &name, Page *pagePointer);
    void triggerEvent(Page::event eventType) override;
private:
    int getLargestLength(std::vector<MenuEntry> entries);
    MenuEntry* getEntryWithName(const std::string& name);
    int getSelected() const;
    std::vector<MenuEntry> menuEntries;
    int selectedEntry;

    Page *getDestinationPage();
};

#endif //CMDPAGES_MENUPAGE_H
