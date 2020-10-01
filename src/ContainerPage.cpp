//
// Created by daniel on 04/11/18.
//

#include "ContainerPage.h"

ContainerPage::ContainerPage(Box *contentPointer) : Page() {
    content = contentPointer;
}

void ContainerPage::display() {
    Page::display();
    content->display();
}

void ContainerPage::setContent(Box *contentPointer) {
    content = contentPointer;
}

Box* ContainerPage::getBox(){
    return content;
}