//
// Created by daniel on 04/11/18.
//

#ifndef CMDPAGES_EMPTYPAGE_H
#define CMDPAGES_EMPTYPAGE_H

#include "Page.h"
#include "Box.h"

class ContainerPage : public Page {
public:
    void setContent(Box *contentPointer);
    void display() override;
    explicit ContainerPage(Box *contentPointer);
    Box* getBox();
private:
    Box *content;
};

#endif //CMDPAGES_EMPTYPAGE_H
