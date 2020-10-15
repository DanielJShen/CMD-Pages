//
// Created by Daniel on 15/10/2020.
//

#ifndef CMDPAGES_PAGESCORE_H
#define CMDPAGES_PAGESCORE_H

#include <vector>
#include "PageWithBox.h"
#include "MenuBox.h"
#include "Logger.h"
#include "FileBrowserBox.h"

class PagesCore {
public:
    PagesCore(PageWithBox* initialPage);
    void init();
    void startPageLoop();
    void changePage(Page* page);
private:
    PageWithBox* initialPage;
    PageWithBox* currentPage;
    bool continuePageLoop = true;
};


#endif //CMDPAGES_PAGESCORE_H
