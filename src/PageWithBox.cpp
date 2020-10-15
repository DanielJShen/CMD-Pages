//
// Created by daniel on 04/11/18.
//

#include "PageWithBox.h"

PageWithBox::PageWithBox(Box *contentPointer) : Page() {
    content = contentPointer;
}

void PageWithBox::display() {
    Page::display();
    content->display();
}

void PageWithBox::updateSize() {
    Page::updateSize();
    content->updateSize();
}

void PageWithBox::setContent(Box *contentPointer) {
    content = contentPointer;
}

Box* PageWithBox::getBox(){
    return content;
}