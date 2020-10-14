#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <vector>
#include "ContainerPage.h"
#include "MenuBox.h"
#include "Logger.h"

void init();
void displayPageLoop(ContainerPage containerPage);

int main() {
    Logger::initLogger("CMDPages.log");
    init();

    std::vector<std::string> options = {"2nd Menu","Example 1","test1","test2"};
    MenuBox* initialMenuBox = MenuBox::makeMenuBox(options);
    ContainerPage initialContainerPage(initialMenuBox);

    std::vector<std::string> options2 = {"Example 2","Even Example 2","Final Example","jklmnopqr"};
    MenuBox* menuBox2 = MenuBox::makeMenuBox(options2);
    ContainerPage containerPage2(menuBox2);

    initialMenuBox->setDestinationPageByName(std::string("2nd Menu"),&containerPage2);

    displayPageLoop(initialContainerPage);

    return 0;
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

void displayPageLoop(ContainerPage containerPage){
    curs_set(0);
    noecho();
    cbreak();
    containerPage.display();

    ContainerPage* currentPage = &containerPage;
    int input;
    while(true) {
        auto * menuBox = (MenuBox*) currentPage->getBox();
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
                menuBox->moveSelectionUp();
            } else if (input == 'B') { // \033[B = Down
                menuBox->moveSelectionDown();
            } else if (input == ERR) { // No input
                if (currentPage->getPreviousPage() != nullptr) {
                    currentPage = (ContainerPage *) currentPage->getPreviousPage();
                    currentPage->updateSize();
                } else {
                    break;
                }
            }

        } else if (input == 10) { // 10 = Enter
            try {
                ContainerPage *page = menuBox->getDestinationPage();
                page->setPreviousPage(currentPage);
                currentPage = page;
                currentPage->updateSize();
            } catch (const std::runtime_error &e) {
                printf("Error: %s\r", e.what());
            }
        } else if (input == KEY_RESIZE) {
            currentPage->updateSize();
        }
        currentPage->display();
    }
    endwin();
    printf("\n");
}