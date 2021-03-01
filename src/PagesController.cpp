//
// Created by Daniel on 15/10/2020.
//

#include "PagesController.h"

PagesController::PagesController() {
    Logger::initLogger("CMDPages.log");
    init();
}

void PagesController::init(){
    Logger::appendMessage("Initializing curses...");
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    if(has_colors() == FALSE) {
        endwin();
        printf("This terminal does not support color\n");
        exit(1);
    }
    start_color();
    wrefresh(stdscr);
    Logger::appendMessage("Curses Initialized!");
}

void PagesController::startPageLoop(Page* initialPage){
    currentPage = initialPage;

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

void PagesController::changePage(Page* page) {
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

void PagesController::executeExternalLinuxCommand(const std::string& command) {
    def_prog_mode();
    endwin();

    system(command.c_str());

    reset_prog_mode();
    refresh();
}

std::string PagesController::executeLinuxCommand(const std::string &command) {
    def_prog_mode();
    endwin();

    std::array<char, 128> buffer = {};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        Logger::appendMessage("Unable to run command! popen() failed!");
    } else {
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
    }

    reset_prog_mode();
    refresh();
    return result;
}
