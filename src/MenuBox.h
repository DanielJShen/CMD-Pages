//
// Created by daniel on 06/11/18.
//

#ifndef CMDPAGES_MENUBOX_H
#define CMDPAGES_MENUBOX_H

#include "Box.h"
#include <string>
#include <vector>

class MenuBox : public Box {
public:
    MenuBox(int x,int y);
    MenuBox(int x,int y, std::vector<std::string> entries);
    void display() override;
    void addMenuEntry(std::string text);
private:
    std::vector<std::string> menuEntries;
};

//#include "MenuBox.cpp"

#endif //CMDPAGES_MENUBOX_H
