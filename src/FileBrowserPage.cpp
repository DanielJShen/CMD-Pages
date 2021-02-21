//
// Created by Daniel on 14/10/2020.
//

#include "FileBrowserPage.h"
#include "FileSystemReader.h"
#include <unistd.h>

#include <utility>

#define BOX_HIGHLIGHT_COLOUR_PAIR 1
#define BOX_HIGHLIGHT_DIRECTORY_COLOUR_PAIR 4
#define BOX_DIRECTORY_COLOUR_PAIR 5
#define BOX_HIGHLIGHT_EXECUTABLE_COLOUR_PAIR 6
#define BOX_EXECUTABLE_COLOUR_PAIR 7

FileBrowserPage::FileBrowserPage(std::string name, const std::string& path, IInputProcessor& inputProcessor) : Page(std::move(name),calculateWindowDimensions(path,".*"),inputProcessor) {
    selectedFile = 0;
    directoryPath = path;
    discoveredFiles = FileSystemReader::getDirectoryContents(directoryPath, ".*");
}

FileBrowserPage::FileBrowserPage(std::string name, const std::string& path, const std::string& filter, IInputProcessor& inputProcessor) : Page(std::move(name),calculateWindowDimensions(path,filter),inputProcessor) {
    selectedFile = 0;
    directoryPath = path;
    discoveredFiles = FileSystemReader::getDirectoryContents(directoryPath, filter);
}

std::array<int, 2> FileBrowserPage::calculateWindowDimensions(const std::string& path, const std::string& filter) {
    std::vector<std::filesystem::directory_entry> files = FileSystemReader::getDirectoryContents(path, filter);

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

void FileBrowserPage::triggerEvent(const PageCallback &changePageCallback, IInputProcessor::inputEvent eventType) {
    switch (eventType) {
        case IInputProcessor::UpKey:
            if (!discoveredFiles.empty()) {
                int newSelectedEntry = selectedFile - 1;
                if(newSelectedEntry < 0){
                    newSelectedEntry = (int)discoveredFiles.size() - 1;
                }
                selectedFile = newSelectedEntry;
            }
            display();
            break;
        case IInputProcessor::DownKey:
            if (!discoveredFiles.empty()) {
                int newSelectedEntry = selectedFile + 1;
                if(newSelectedEntry >= discoveredFiles.size()){
                    newSelectedEntry = 0;
                }
                selectedFile = newSelectedEntry;
            }
            display();
            break;
        case IInputProcessor::EnterKey:
            //TODO Do action on selection of file
            break;
        case IInputProcessor::EscapeKey:
            changePageCallback(nullptr);
            break;
        case IInputProcessor::Resize:
            updateSize();
            display();
            break;
    };
}

Page *FileBrowserPage::getDestinationPage() {
    //TODO open a new file browser for sub dir?
    return nullptr;
}
