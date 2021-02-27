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
    /** A page which displays the content of a directory at the given path.
     *  When an entry is selected the actions performed depend on the functions provided to setOnSelectDirectory and setOnSelectFile.
     * @param name Name of the page
     * @param path Path to a directory who's content will be displayed.
     * @param inputProcessor An implementation of IInputProcessor to get inputs from the keyboard.
     */
    FileBrowserPage(std::string name, const std::string &path, IInputProcessor& inputProcessor);

    /** A page which displays the content of a directory at the given path which matches the regex filter provided.
     *  When an entry is selected the actions performed depend on the functions provided to setOnSelectDirectory and setOnSelectFile.
     * @param name Name of the page
     * @param path Path to a directory who's content will be displayed.
     * @param filter Regex filter, only matching entries will be shown.
     * @param inputProcessor An implementation of IInputProcessor to get inputs from the keyboard.
     */
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

    typedef std::function<void(const std::filesystem::directory_entry&, FileBrowserPage*)> FileActionCallback;
    FileActionCallback* onSelectDirectory = nullptr;
    FileActionCallback* onSelectFile = nullptr;
    void setOnSelectDirectory(FileActionCallback* onSelectDirectory);
    void setOnSelectFile(FileActionCallback* onSelectFile);

private:
    static std::array<int, 2> calculateWindowDimensions(const std::string& name, const std::string& path, const std::string& filter);
    std::filesystem::path directoryPath;
    std::vector<std::filesystem::directory_entry> discoveredFiles;
    int selectedFileIndex;

    NCURSES_COLOR_T colour_directory;
    NCURSES_COLOR_T colour_highlightDirectory;
    NCURSES_COLOR_T colour_executable;
    NCURSES_COLOR_T colour_highlightExecutable;

    void triggerEvent(const PageCallback &changePageCallback, KeyInput eventType) override;
};


#endif //CMDPAGES_FILEBROWSERPAGE_H
