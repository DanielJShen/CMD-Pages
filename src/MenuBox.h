//
// Created by daniel on 06/11/18.
//

#ifndef CMDPAGES_MENUBOX_H
#define CMDPAGES_MENUBOX_H

#include "Box.h"
#include "ContainerPage.h"
#include <string>
#include <vector>
#include <map>

class MenuBox : public Box {
public:
    MenuBox(int x,int y);
    MenuBox(int x,int y, std::vector<std::string> entries);
    MenuBox(int width, std::vector<std::string> entries);
    void display() override;
    void setSelected(int position);
    int getSelected();
    ContainerPage* getSelectionPage();
    void setEntryPage(int entry, ContainerPage* pagePointer);
    void addMenuEntry(std::string text);
private:
    std::string menuName = "Menu";
    std::vector<std::string> menuEntries;
    std::map<int,ContainerPage*> menuEntryContents;
    int selectedEntry;
};

//#include "MenuBox.cpp"

#endif //CMDPAGES_MENUBOX_H
