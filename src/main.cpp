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

    std::vector<std::string> options = {"a","b","c"};
    MenuBox box(60,12,options);
    EmptyPage emptyPage(&box);
    //emptyPage.setContent(&box);

    curs_set(0);
    emptyPage.display();

    getch(); //Will refresh if changes to win are not refreshed.
    endwin();
    printf("\n");
    return 0;
}