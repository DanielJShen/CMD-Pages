#include <vector>
#include "Page.h"
#include "MenuPage.h"
#include "Logger.h"
#include "FileBrowserPage.h"
#include "PagesDisplayLoop.h"

int main() {
    Logger::initLogger("CMDPages.log");

    PagesDisplayLoop pagesCore = PagesDisplayLoop();

    Page testPage1 = Page("Test1",{40,10});
    MenuPage menuPage1 = MenuPage("Menu1", {&testPage1});
    MenuPage menuPage2 = MenuPage("Menu2", {});
    FileBrowserPage fileBrowserPage = FileBrowserPage("File Browser 1",".",".*");

    MenuPage initialPage = MenuPage("Main Menu", {&menuPage1,&menuPage2,&fileBrowserPage});

    pagesCore.startPageLoop(&initialPage);

    return 0;
}
