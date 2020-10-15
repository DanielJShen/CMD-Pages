#include <vector>
#include "PageWithBox.h"
#include "MenuBox.h"
#include "Logger.h"
#include "FileBrowserBox.h"
#include "PagesCore.h"

int main() {
    std::vector<std::string> options = {"2nd Menu","File Browser","test1","test2"};
    MenuBox* initialMenuBox = MenuBox::makeMenuBox("1st Menu",options);
    PageWithBox initialPage(initialMenuBox);

    std::vector<std::string> options2 = {"Example 2","test1","test2","test3"};
    MenuBox* menuBox2 = MenuBox::makeMenuBox("2nd Menu",options2);
    PageWithBox menuPage2(menuBox2);

    FileBrowserBox* fileBrowserBox2 = FileBrowserBox::makeFileBrowserBox("File Browser 1",".");
    PageWithBox fileBrowserPage3(fileBrowserBox2);

    initialMenuBox->setDestinationPageByName(std::string("2nd Menu"),&menuPage2);
    initialMenuBox->setDestinationPageByName(std::string("File Browser"),&fileBrowserPage3);

    PagesCore pagesCore = PagesCore(&initialPage);
    pagesCore.startPageLoop();

    return 0;
}
