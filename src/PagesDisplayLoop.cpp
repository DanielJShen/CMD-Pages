//
// Created by Daniel on 15/10/2020.
//

#include "PagesDisplayLoop.h"

PagesDisplayLoop::PagesDisplayLoop() {
    Logger::initLogger("CMDPages.log");
    init();
}

void PagesDisplayLoop::init(){
    Logger::appendMessage("Initializing");
    initscr();
    cbreak();

    if(has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    wrefresh(stdscr);
}

void PagesDisplayLoop::startPageLoop(Page* initialPage){
    currentPage = initialPage;

    curs_set(0);
    noecho();
    cbreak();
    initialPage->display();
    try {
        while (continuePageLoop) { //TODO Change to a multithreaded event based system
            currentPage->iterate([this](auto &&PH1) { changePage(PH1); });
        }
    } catch (std::runtime_error& error) {
        endwin();
        printf("\n");
        throw error;
    }
    endwin();
    printf("\n");
}

/** A callback for changing the currently displayed page.
 *
 * @param page A pointer to a page to display or nullptr to display the previously page.
 */
void PagesDisplayLoop::changePage(Page* page) {
    Logger::appendMessage("Changing page:"+std::to_string((long)page));
    if (page != nullptr) {
        page->setPreviousPage(currentPage);
        currentPage = dynamic_cast<Page *>(page);
        currentPage->updateSize();
        currentPage->display();
    } else {
        if (currentPage->getPreviousPage() != nullptr) {
            currentPage = (Page *) currentPage->getPreviousPage();
            currentPage->updateSize();
            currentPage->display();
        } else {
            continuePageLoop = false;
        }
    }
}