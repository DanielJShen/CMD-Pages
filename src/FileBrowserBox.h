//
// Created by Daniel on 14/10/2020.
//

#ifndef CMDPAGES_FILEBROWSERBOX_H
#define CMDPAGES_FILEBROWSERBOX_H


#include "Logger.h"
#include "Box.h"
#include <vector>
#include <filesystem>
#include <iostream>
#include <regex>
#include <string>

class FileBrowserBox : public Box {
public:
    FileBrowserBox(int width, int height, const std::string &name, const std::string &path, const std::string &filter);
    static FileBrowserBox *makeFileBrowserBox(const std::string& name, const std::string& path);
    static FileBrowserBox *makeFileBrowserBox(const std::string& name, const std::string& path, const std::string& filter);
    void display();
    void triggerEvent(Box::event eventType, const std::function<void(PagesCore::*)(Page*)> &changePageCallback) override;

private:
    std::string boxName = "File Browser";
    std::filesystem::path directoryPath;
    std::string fileFilter;
    std::vector<std::filesystem::directory_entry> files;
    int selectedFile = 0;
    void loadFiles(const std::filesystem::path& path);

};


#endif //CMDPAGES_FILEBROWSERBOX_H
