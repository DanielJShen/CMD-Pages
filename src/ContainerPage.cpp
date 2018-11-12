//
// Created by daniel on 04/11/18.
//

#include "ContainerPage.h"

EmptyPage::EmptyPage(Box *contentPointer) : Page() {
    content = contentPointer;
}

void EmptyPage::display() {
    Page::display();
    content->display();
}

void EmptyPage::setContent(Box *contentPointer) {
    content = contentPointer;
}
