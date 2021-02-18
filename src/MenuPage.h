//
// Created by daniel on 06/11/18.
//

#ifndef CMDPAGES_MENUPAGE_H
#define CMDPAGES_MENUPAGE_H

#include "Page.h"
#include <string>
#include <vector>
#include <map>

/** A Page which contains a list of MenuEntries. One can be selected in order to go to the respective page.
 *
 */
class MenuPage : public Page {
public:
    MenuPage(std::string name, std::vector<Page*> pages);

    void display() override;
    void updateSize() override;
    void destroy() override;

private:
    std::array<int, 2> calculateWindowDimensions(const std::string& name, const std::vector<Page*>& pages);
    int getLargestPageNameLength(const std::string& name, const std::vector<Page*>& entries);
    Page* getPageWithName(const std::string& name);
    int getSelected();
    std::vector<Page*> availablePages;
    int selectedEntry;

    void triggerEvent(const PageCallback &changePageCallback, InputProcessor::inputEvent eventType) override;
    Page* getPagePointerForSelectedMenuEntry();
};

#endif //CMDPAGES_MENUPAGE_H
