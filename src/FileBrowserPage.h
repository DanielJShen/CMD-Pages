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

    void display() override;
    void updateSize() override;
    void destroy() override;

private:
    std::array<int, 2> calculateWindowDimensions(const std::string& path, const std::string& filter);
    std::string directoryPath;
    std::vector<std::filesystem::directory_entry> discoveredFiles;
    int selectedFile;

    void triggerEvent(const PageCallback &changePageCallback, IInputProcessor::inputEvent eventType) override;
    Page *getDestinationPage();
};


#endif //CMDPAGES_FILEBROWSERPAGE_H
