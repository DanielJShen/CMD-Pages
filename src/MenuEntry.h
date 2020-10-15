//
// Created by Daniel on 11/10/2020.
//

#ifndef CMDPAGES_MENUENTRY_H
#define CMDPAGES_MENUENTRY_H

#include <string>
#include "PageWithBox.h"

/** An entry in a MenuBox.
 * The entry has text to be displayed and a pagePointer to indicate the page which is displayed when the entry is selected.
 *
 */
class MenuEntry {
public:
    MenuEntry(std::string name, PageWithBox* pagePointer);

    explicit MenuEntry(std::string& name);

    void setDestinationPage(PageWithBox* containerPage);

    std::string getName() const;
    PageWithBox* getDestinationPage();

private:
    std::string entryText;
    PageWithBox* pagePointer;
};


#endif //CMDPAGES_MENUENTRY_H
