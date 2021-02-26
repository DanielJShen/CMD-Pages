# CMD-Pages
A library for a colourful interactive menu for the linux command line. Similar to the command 'dialog'.

## Building
Build using CLion on Ubuntu 18.04

CMDPages_lib requires libraries: ncurses \
CMDPagesTest requires libraries: gtest, gmock

Build commands: \
cmake --build {PATH_TO_PROJECT}/CMD-Pages/build/ --target CMDPages \
cmake --build {PATH_TO_PROJECT}/CMD-Pages/build/ --target CMDPagesTest \
cmake --build {PATH_TO_PROJECT}/CMD-Pages/build/ --target CMDPages_example 

## Usage
The CMDPages_example executable is an example menu which uses the CMDPages library, to create your own interactive menu you can use CMDPages_lib. \
CMDPagesTest can be run to test CMDPages_lib.

### CMDPages_lib
#### Main Classes:

- Page
- MenuPage
- FileBrowserPage
- PagesDisplayLoop

Basic page setup:  

    PagesDisplayLoop pagesDisplayLoop = PagesDisplayLoop();
    Page emptyPage = Page("EmptyPage",{40,10});
    MenuPage initialPage = MenuPage("Main Menu", {&emptyPage});
    pagesCore.startPageLoop(&initialPage);