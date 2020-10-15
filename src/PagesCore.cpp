//
// Created by Daniel on 15/10/2020.
//

#include "PagesCore.h"
#include <unistd.h>

PagesCore::PagesCore(PageWithBox* initialPage) {
    Logger::initLogger("CMDPages.log");
    init();
    this->initialPage = initialPage;
}

void init(){
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

void PagesCore::startPageLoop(){
    curs_set(0);
    noecho();
    cbreak();
    initialPage->display();

    currentPage = initialPage;
    int input;
    while(continuePageLoop) {
        auto * menuBox = currentPage->getBox();
        input = wgetch(menuBox->window);
        if(input == 27) { // 27 = Esc code

            //Code block is equivalent to keypad mode in getch but with a shorter wait when pressing ESC
            nodelay(menuBox->window,true);
            int count = 0;
            do {
                input = wgetch(menuBox->window);//Gets the [ character from escape codes or ERR when ESC is pressed
                count++;
                usleep(10);
            } while(input == ERR && count < 100);
            input = wgetch(menuBox->window);
            nodelay(menuBox->window,false);

            if (input == 'A') { // \033[A = Up
                menuBox->triggerEvent(Box::UpKey, &PagesCore::changePage);
            } else if (input == 'B') { // \033[B = Down
                menuBox->triggerEvent(Box::DownKey, &PagesCore::changePage);
            } else if (input == ERR) { // No input or Escape
                menuBox->triggerEvent(Box::EscapeKey, &PagesCore::changePage);
            }

        } else if (input == 10) { // 10 = Enter
            menuBox->triggerEvent(Box::EnterKey, &PagesCore::changePage);
        } else if (input == KEY_RESIZE) {
            currentPage->updateSize();
        } else {
            continue;
        }
        currentPage->display();
    }
    endwin();
    printf("\n");
}

/** A callback for changing the currently displayed page.
 *
 * @param page A pointer to a page to display or nullptr to display the previously page.
 */
void PagesCore::changePage(Page* page) {
    Logger::appendMessage("Changing page:"+std::to_string((long)page));
    if (page != nullptr) {
        page->setPreviousPage(currentPage);
        currentPage = dynamic_cast<PageWithBox *>(page);

        currentPage->updateSize();
        currentPage->display();
    } else {
        if (currentPage->getPreviousPage() != nullptr) {
            currentPage = (PageWithBox *) currentPage->getPreviousPage();
            currentPage->updateSize();
            currentPage->display();
        } else {
            continuePageLoop = false;
        }
    }
}