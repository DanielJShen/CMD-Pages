//
// Created by Daniel on 14/10/2020.
//

#ifndef CMDPAGES_FILEBROWSERPAGE_H
#define CMDPAGES_FILEBROWSERPAGE_H

#include "Logger.h"
#include "Page.h"
#include <vector>
#include <filesystem>
#include <iostream>
#include <regex>
#include <string>

class FileBrowserPage : public Page {
public:
    FileBrowserPage(std::string name, const std::string &path, IInputProcessor& inputProcessor);
    FileBrowserPage(std::string name, const std::string &path, const std::string &filter, IInputProcessor& inputProcessor);

    /**
     *
     * @param directory Text colour for directories
     *               <br> Default: COLOR_LIGHTBLUE (custom colour, use value 11)
     * @param highlightDirectory Text colour for directories when highlighted
     *               <br> Default: COLOR_LIGHTBLUE (custom colour, use value 11)
     * @param executable Text colour for executables
     *               <br> Default: COLOR_GREEN
     * @param highlightExecutable Text colour for executables when highlighted
     *               <br> Default: COLOR_GREEN
     */
    void setFileBrowserColours(NCURSES_COLOR_T directory, NCURSES_COLOR_T highlightDirectory, NCURSES_COLOR_T executable, NCURSES_COLOR_T highlightExecutable);

    void display() override;
    void updateSize() override;
    void destroy() override;

private:
    std::array<int, 2> calculateWindowDimensions(const std::string& path, const std::string& filter);
    std::string directoryPath;
    std::vector<std::filesystem::directory_entry> discoveredFiles;
    int selectedFile;

    NCURSES_COLOR_T colour_directory;
    NCURSES_COLOR_T colour_highlightDirectory;
    NCURSES_COLOR_T colour_executable;
    NCURSES_COLOR_T colour_highlightExecutable;

    void triggerEvent(const PageCallback &changePageCallback, IInputProcessor::inputEvent eventType) override;
    Page *getDestinationPage();
};


#endif //CMDPAGES_FILEBROWSERPAGE_H
