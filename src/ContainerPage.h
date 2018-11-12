//
// Created by daniel on 04/11/18.
//

#ifndef CMDPAGES_EMPTYPAGE_H
#define CMDPAGES_EMPTYPAGE_H

#include "Page.h"
#include "Box.h"

class EmptyPage : public Page {
public:
    void setContent(Box *contentPointer);
    void display();
    EmptyPage(Box *contentPointer);
    EmptyPage();
private:
    Box *content;
};

//#include "EmptyPage.cpp"

#endif //CMDPAGES_EMPTYPAGE_H
