//
// Created by Daniel on 11/10/2020.
//

#ifndef CMDPAGES_MENUENTRY_H
#define CMDPAGES_MENUENTRY_H

#include <string>
#include "ContainerPage.h"

/** An entry in a MenuBox.
 * The entry has text to be displayed and a pagePointer to indicate the page which is displayed when the entry is selected.
 *
 */
class MenuEntry {
public:
    MenuEntry(std::string name, ContainerPage* pagePointer);

    explicit MenuEntry(std::string& name);

    void setDestinationPage(ContainerPage* containerPage);

    std::string getName() const;
    ContainerPage* getDestinationPage();

private:
    std::string entryText;
    ContainerPage* pagePointer;
};


#endif //CMDPAGES_MENUENTRY_H
