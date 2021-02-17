//
// Created by Daniel on 14/10/2020.
//

#include "FileBrowserPage.h"
#include <unistd.h>

#define BOX_HIGHLIGHT_COLOUR_PAIR 1
#define BOX_HIGHLIGHT_DIRECTORY_COLOUR_PAIR 4
#define BOX_DIRECTORY_COLOUR_PAIR 5
#define BOX_HIGHLIGHT_EXECUTABLE_COLOUR_PAIR 6
#define BOX_EXECUTABLE_COLOUR_PAIR 7

FileBrowserPage::FileBrowserPage(std::string name, const std::string& path) : Page(name,calculateWindowDimensions(path,".*")) {
    selectedFile = 0;
    directoryPath = path;
    discoveredFiles = loadFiles(directoryPath, ".*");
}

FileBrowserPage::FileBrowserPage(std::string name, const std::string& path, const std::string& filter) : Page(name,calculateWindowDimensions(path,filter)) {
    selectedFile = 0;
    directoryPath = path;
    discoveredFiles = loadFiles(directoryPath, filter);
}

std::array<int, 2> FileBrowserPage::calculateWindowDimensions(const std::string& path, const std::string& filter) {
    std::vector<std::filesystem::directory_entry> files = loadFiles(path, filter);

    int highestLength = 0;
    int fileCount = 0;
    for (auto& file : files) {
        int entryLength = file.path().filename().string().length();
        if (entryLength > highestLength) {
            highestLength = entryLength;
        }
        fileCount++;
    }
    int width = (int) highestLength + 15;
    int height = (int) fileCount + 6;
    return {width,height};
}

void FileBrowserPage::display() {
    //mvwprintw(contentWindow,0,2,"%s",boxName.c_str());
    mvwprintw(contentWindow,2,4,"%s",directoryPath.c_str());
    for (int i = 0; i < discoveredFiles.size(); i++) {
        std::string filename = discoveredFiles[i].path().filename();
        bool isDirectory = discoveredFiles[i].is_directory();
        if(selectedFile == i){
            if (isDirectory) {
                wattron(contentWindow, COLOR_PAIR(BOX_HIGHLIGHT_DIRECTORY_COLOUR_PAIR));
            } else {
                wattron(contentWindow, COLOR_PAIR(BOX_HIGHLIGHT_COLOUR_PAIR));
            }
        } else if (isDirectory){
            wattron(contentWindow, COLOR_PAIR(BOX_DIRECTORY_COLOUR_PAIR));
        }
        mvwprintw(contentWindow,i+3, 5, "- %s", filename.c_str());
        wattroff(contentWindow,COLOR_PAIR(BOX_HIGHLIGHT_COLOUR_PAIR));
    }
    Page::display();
}

void FileBrowserPage::updateSize() {
    Page::updateSize();
}

void FileBrowserPage::destroy() {
    Page::destroy();
}

std::vector<std::filesystem::directory_entry> FileBrowserPage::loadFiles(const std::string& path,const std::string& fileFilter) {
    std::string absolutePath = std::regex_replace(path,std::regex("^\\."),std::filesystem::current_path().string());
    Logger::appendMessage("File Browser - Absolute Path: "+absolutePath);

    std::vector<std::filesystem::directory_entry> files = {};
    if (fileFilter == ".*") {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(absolutePath)) {
            Logger::appendMessage("File Browser - File Found: "+entry.path().filename().string()+" Regex Match: "+ std::to_string(std::regex_match(entry.path().filename().string(), std::regex(fileFilter))) );
                files.push_back(entry);
        }
    } else {
        for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(absolutePath)) {
            Logger::appendMessage("File Browser - File Found: " + entry.path().filename().string() + " Regex Match: " +
                                  std::to_string(
                                          std::regex_match(entry.path().filename().string(), std::regex(fileFilter))));
            if (std::regex_match(entry.path().filename().string(), std::regex(fileFilter))) {
                files.push_back(entry);
            }
        }
    }
    return files;
}

/** Triggers an event on the Box
 *
 * @param eventType The event being triggered
 * @param changePageCallback A callback for changing the currently displayed page
 */
void FileBrowserPage::triggerEvent(const PageCallback &changePageCallback, Page::event eventType) {
    switch (eventType) {
        case UpKey:
            if (!discoveredFiles.empty()) {
                int newSelectedEntry = selectedFile - 1;
                if(newSelectedEntry < 0){
                    newSelectedEntry = (int)discoveredFiles.size() - 1;
                }
                selectedFile = newSelectedEntry;
            }
            display();
            break;
        case DownKey:
            if (!discoveredFiles.empty()) {
                int newSelectedEntry = selectedFile + 1;
                if(newSelectedEntry >= discoveredFiles.size()){
                    newSelectedEntry = 0;
                }
                selectedFile = newSelectedEntry;
            }
            display();
            break;
        case EnterKey:
            //TODO Do action on selection of file
            break;
        case EscapeKey:
            changePageCallback(nullptr);
            break;
        case Resize:
            updateSize();
            display();
            break;
    };
}

Page *FileBrowserPage::getDestinationPage() {
    //TODO open a new file browser for sub dir?
    return nullptr;
}
