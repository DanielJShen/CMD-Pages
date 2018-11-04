#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "Page.h"

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

    Page page;
    curs_set(0);
    page.display();

    getch(); //Will refresh if changes to win are not refreshed.
    endwin();
    return 0;
}