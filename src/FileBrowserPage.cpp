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

FileBrowserPage::FileBrowserPage(const std::string& name, const std::string& path) : Page() {
    pageName = name;
    selectedFile = 0;
    directoryPath = path;
    fileFilter = ".*";

    loadFiles(directoryPath);

    auto [width,height] = calculateWindowDimensions();
    createWindows(width, height);
}

FileBrowserPage::FileBrowserPage(const std::string& name, const std::string& path, const std::string& filter) : Page() {
    pageName = name;
    selectedFile = 0;
    directoryPath = path;
    fileFilter = filter;

    loadFiles(directoryPath);

    auto [width,height] = calculateWindowDimensions();
    createWindows(width, height);
}

std::array<int, 2> FileBrowserPage::calculateWindowDimensions() {
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

/** This function is run in a loop to detect key presses and update the terminal.
 *
 * @param changePageCallback A callback for changing the page to be iterated over.
 */
void FileBrowserPage::iterate(const PageCallback &changePageCallback) {
    Page::event eventToBeTriggered = processInput();
    if (eventToBeTriggered != Page::NoAction) {
        triggerEvent(changePageCallback, eventToBeTriggered);
    }
}

void FileBrowserPage::display() {
    //mvwprintw(contentWindow,0,2,"%s",boxName.c_str());
    mvwprintw(contentWindow,2,4,"%s",directoryPath.c_str());
    for (int i = 0; i < files.size(); i++) {
        std::string filename = files[i].path().filename();
        bool isDirectory = files[i].is_directory();
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

void FileBrowserPage::loadFiles(const std::string& path) {
    std::string absolutePath = std::regex_replace(path,std::regex("^\\."),std::filesystem::current_path().string());
    Logger::appendMessage("File Browser - Absolute Path: "+absolutePath);

    files = {};
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
}

/** Triggers an event on the Box
 *
 * @param eventType The event being triggered
 * @param changePageCallback A callback for changing the currently displayed page
 */
void FileBrowserPage::triggerEvent(const PageCallback &changePageCallback, Page::event eventType) {
    switch (eventType) {
        case UpKey:
            if (!files.empty()) {
                int newSelectedEntry = selectedFile - 1;
                if(newSelectedEntry < 0){
                    newSelectedEntry = (int)files.size() - 1;
                }
                selectedFile = newSelectedEntry;
            }
            display();
            break;
        case DownKey:
            if (!files.empty()) {
                int newSelectedEntry = selectedFile + 1;
                if(newSelectedEntry >= files.size()){
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
