//
// Created by Daniel on 15/10/2020.
//

#ifndef CMDPAGES_PAGESDISPLAYLOOP_H
#define CMDPAGES_PAGESDISPLAYLOOP_H

#include <vector>
#include "Page.h"
#include "Logger.h"

class PagesDisplayLoop {
public:
    explicit PagesDisplayLoop();
    void init();
    void startPageLoop(Page* initialPage);
    void changePage(Page* page);

    Page* initialPage;
    Page* currentPage;
    bool continuePageLoop = true;
};


#endif //CMDPAGES_PAGESDISPLAYLOOP_H
