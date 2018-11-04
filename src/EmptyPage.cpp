//
// Created by daniel on 04/11/18.
//

#include "EmptyPage.h"

EmptyPage::EmptyPage(Box *contentPointer) {
    content = contentPointer;
}
EmptyPage::EmptyPage() {
}

void EmptyPage::setContent(Box *contentPointer) {
    content = contentPointer;
}
