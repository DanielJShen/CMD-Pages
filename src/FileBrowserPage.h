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
    FileBrowserPage(std::string name, const std::string &path);
    FileBrowserPage(std::string name, const std::string &path, const std::string &filter);

    void display() override;
    void updateSize() override;
    void destroy() override;

    void triggerEvent(const PageCallback &changePageCallback, Page::event eventType) override;

private:
    std::array<int, 2> calculateWindowDimensions(const std::string& path, const std::string& filter);
    std::string directoryPath;
    std::vector<std::filesystem::directory_entry> discoveredFiles;
    int selectedFile;
    std::vector<std::filesystem::directory_entry> loadFiles(const std::string& path, const std::string& fileFilter);

    Page *getDestinationPage();
};


#endif //CMDPAGES_FILEBROWSERPAGE_H
