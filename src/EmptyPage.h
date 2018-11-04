//
// Created by daniel on 04/11/18.
//

#ifndef CMDPAGES_EMPTYPAGE_H
#define CMDPAGES_EMPTYPAGE_H

#import "Page.h"
#import "Box.h"

class EmptyPage : public Page {
public:
    void setContent(Box *contentPointer);
    EmptyPage(Box *contentPointer);
    EmptyPage();
private:
    Box *content;
};

#include "EmptyPage.cpp"

#endif //CMDPAGES_EMPTYPAGE_H
