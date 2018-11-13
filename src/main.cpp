#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "ContainerPage.h"
#include "MenuBox.h"

int main() {
    initscr();
    cbreak();

    if(has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    wrefresh(stdscr);

    std::vector<std::string> options = {"2nd Menu","Even Example 1","Final Example","abcdefghi"};
    MenuBox box(40,options);
    ContainerPage containerPage(&box);

    std::vector<std::string> options2 = {"Example 2","Even Example 2","Final Example","jklmnopqr"};
    MenuBox box2(35,options2);
    ContainerPage containerPage2(&box2);
    box.setEntryPage(0,&containerPage2);

    curs_set(0);
    noecho();
    keypad(stdscr,true);
    cbreak();
    containerPage.display();

    int input = wgetch(stdscr);
    ContainerPage* currentPage = &containerPage;
    while(input != 27) { // 27 = Esc
        auto * menuBox = (MenuBox*) currentPage->getBox();

        if(input == 259) { // 259 = Up
            menuBox->setSelected(menuBox->getSelected()-1);
        } else if(input == 258) { // 258 = Down
            menuBox->setSelected(menuBox->getSelected()+1);
        } else if(input == 10) { // 10 = Enter
            try {
                ContainerPage *page = menuBox->getSelectionPage();
                currentPage = page;
            } catch( const std::runtime_error& e) {
                printf("Error: %s\r",e.what());
            }

        }
        currentPage->display();
        input = wgetch(stdscr);
    }

    endwin();
    printf("\n");
    return 0;
}