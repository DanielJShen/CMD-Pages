#include <vector>
#include "Page.h"
#include "MenuPage.h"
#include "Logger.h"
#include "FileBrowserPage.h"
#include "PagesDisplayLoop.h"
#include "BlockingInputProcessor.h"

#define COLOR_LIGHTBLUE 11

int main() {
    Logger::initLogger("CMDPages.log");

    PagesDisplayLoop pagesCore = PagesDisplayLoop();

    Page testPage1 = Page("Test1",{40,10}, UseBlockingInputProcessor());
    testPage1.setColours(COLOR_BLACK,COLOR_BLACK,COLOR_BLUE,COLOR_CYAN,COLOR_BLACK,COLOR_BLUE);
//    Page::setUseGlobalColours(TRUE);

    MenuPage menuPage1 = MenuPage("Menu1", {&testPage1}, UseBlockingInputProcessor());
    MenuPage menuPage2 = MenuPage("Menu2", {}, UseBlockingInputProcessor());
    FileBrowserPage fileBrowserPage = FileBrowserPage("File Browser 1",".",".*", UseBlockingInputProcessor());
    fileBrowserPage.setFileBrowserColours(COLOR_LIGHTBLUE,COLOR_LIGHTBLUE,COLOR_GREEN,COLOR_GREEN);

    MenuPage initialPage = MenuPage("Main Menu", {&menuPage1,&menuPage2,&fileBrowserPage}, UseBlockingInputProcessor());
    pagesCore.startPageLoop(&initialPage);

    return 0;
}
