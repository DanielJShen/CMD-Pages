#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "EmptyPage.h"

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

    EmptyPage emptyPage;
    curs_set(0);
    emptyPage.display();

    getch(); //Will refresh if changes to win are not refreshed.
    endwin();
    return 0;
}