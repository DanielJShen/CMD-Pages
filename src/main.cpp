#include <vector>
#include "Page.h"
#include "MenuPage.h"
#include "Logger.h"
#include "FileBrowserPage.h"
#include "PagesDisplayLoop.h"

int main() {
    Logger::initLogger("CMDPages.log");

    PagesDisplayLoop pagesCore = PagesDisplayLoop();

    std::vector<std::string> options = {"2nd Menu","File Browser","test1","test2"};
    MenuPage initialPage = MenuPage("1st Menu", options);

    std::vector<std::string> options2 = {"Example 2","test1","test2","test3"};
    MenuPage menuPage2 = MenuPage("2nd Menu", options2);

    FileBrowserPage fileBrowserPage = FileBrowserPage("File Browser 1",".",".*");

    initialPage.setDestinationPageByName(std::string("2nd Menu"),&menuPage2);
    initialPage.setDestinationPageByName(std::string("File Browser"),&fileBrowserPage);

    pagesCore.startPageLoop(&initialPage);

    return 0;
}
