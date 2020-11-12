////
//// Created by Daniel on 14/10/2020.
////
//
//#ifndef CMDPAGES_FILEBROWSERPAGE_H
//#define CMDPAGES_FILEBROWSERPAGE_H
//
//
//#include "Logger.h"
//#include "Page.h"
//#include <vector>
//#include <filesystem>
//#include <iostream>
//#include <regex>
//#include <string>
//
//class FileBrowserPage : public Page {
//public:
//    FileBrowserPage(int width, int height, const std::string &name, const std::string &path, const std::string &filter);
//    static FileBrowserPage *makeFileBrowserBox(const std::string& name, const std::string& path);
//    static FileBrowserPage *makeFileBrowserBox(const std::string& name, const std::string& path, const std::string& filter);
//    void display();
//    void triggerEvent(Page::event eventType, std::function<void(Page*)> &changePageCallback) override;
//
//private:
//    std::string boxName = "File Browser";
//    std::filesystem::path directoryPath;
//    std::string fileFilter;
//    std::vector<std::filesystem::directory_entry> files;
//    int selectedFile = 0;
//    void loadFiles(const std::filesystem::path& path);
//
//};
//
//
//#endif //CMDPAGES_FILEBROWSERPAGE_H
