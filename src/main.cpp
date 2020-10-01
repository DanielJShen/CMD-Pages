#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "ContainerPage.h"
#include "MenuBox.h"

void init();
void mainloop(ContainerPage containerPage);

int main() {
    init();

    std::vector<std::string> options = {"2nd Menu","Even Example 1","Final Example","abcdefghi"};
    MenuBox box(40,options);
    ContainerPage containerPage(&box);

    std::vector<std::string> options2 = {"Example 2","Even Example 2","Final Example","jklmnopqr"};
    MenuBox box2(35,options2);
    ContainerPage containerPage2(&box2);
    box.setEntryPage(0,&containerPage2);

    mainloop(containerPage);

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

void mainloop(ContainerPage containerPage){
    curs_set(0);
    noecho();
    cbreak();
    containerPage.display();

    ContainerPage* currentPage = &containerPage;
    int input = wgetch(currentPage->getBox()->window);
    while(true) {
        auto * menuBox = (MenuBox*) currentPage->getBox();
        if(input == 27) { // 27 = Esc code

            //Code block is equivalent to keypad mode in getch but with a shorter wait when pressing ESC
            nodelay(menuBox->window,true);
            int count = 0;
            do {
                input = wgetch(menuBox->window);//Gets the [ character from escape codes or ERR when ESC was pressed
                count++;
                usleep(10);
            } while(input == ERR && count < 100);
            input = wgetch(menuBox->window);
            nodelay(menuBox->window,false);

            if (input == 'A') { // \033[A = Up
                menuBox->setSelected(menuBox->getSelected() - 1);
            } else if (input == 'B') { // \033[B = Down
                menuBox->setSelected(menuBox->getSelected() + 1);
            } else if (input == ERR) { // No input
                if (currentPage->getPreviousPage() != nullptr) {
                    currentPage = (ContainerPage *) currentPage->getPreviousPage();
                } else {
                    break;
                }
            }

        } else if (input == 10) { // 10 = Enter
            try {
                ContainerPage *page = menuBox->getSelectionPage();
                page->setPreviousPage(currentPage);
                currentPage = page;
            } catch (const std::runtime_error &e) {
                printf("Error: %s\r", e.what());
            }
        }
        currentPage->display();
        input = wgetch(menuBox->window);
    }
    endwin();
    printf("\n");
}