//
// Created by Daniel on 11/10/2020.
//

#ifndef CMDPAGES_MENUENTRY_H
#define CMDPAGES_MENUENTRY_H

#include <string>
#include "Page.h"

/** An entry in a MenuPage.
 * The entry has text to be displayed and a pagePointer to indicate the page which is displayed when the entry is selected.
 *
 */
class MenuEntry {
public:
    MenuEntry(std::string entryName, Page* pagePointer);
    explicit MenuEntry(std::string& entryName);

    void setDestinationPage(Page* containerPage);
    Page* getDestinationPage();

    void setName(std::string& entryName);
    std::string getName();

private:
    std::string entryName;
    Page* pagePointer;
};


#endif //CMDPAGES_MENUENTRY_H
