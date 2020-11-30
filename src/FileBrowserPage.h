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
    FileBrowserPage(const std::string &name, const std::string &path);
    FileBrowserPage(const std::string &name, const std::string &path, const std::string &filter);

    void iterate(const PageCallback &changePageCallback) override;

    void display() override;
    void updateSize() override;
    void destroy() override;

    void triggerEvent(Page::event eventType) override;

private:
    std::array<int, 2> calculateWindowDimensions();
    std::string directoryPath;
    std::string fileFilter;
    std::vector<std::filesystem::directory_entry> files;
    int selectedFile;
    void loadFiles(const std::string& path);

    Page *getDestinationPage();
};


#endif //CMDPAGES_FILEBROWSERPAGE_H
