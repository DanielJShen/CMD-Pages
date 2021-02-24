//
// Created by Daniel on 14/10/2020.
//

#include "FileBrowserPage.h"
#include "FileSystemReader.h"
#include "BlockingInputProcessor.h"
#include <unistd.h>

#include <utility>

#define COLOR_GRAY 9
#define COLOR_DARKGRAY 10
#define COLOR_LIGHTBLUE 11

#define BOX_HIGHLIGHT_COLOUR_PAIR 1
#define BOX_DIRECTORY_COLOUR_PAIR 4
#define BOX_HIGHLIGHT_DIRECTORY_COLOUR_PAIR 5
#define BOX_EXECUTABLE_COLOUR_PAIR 6
#define BOX_HIGHLIGHT_EXECUTABLE_COLOUR_PAIR 7

FileBrowserPage::FileBrowserPage(std::string name, const std::string& path, IInputProcessor& inputProcessor) : FileBrowserPage(std::move(name),path,".*",inputProcessor) {
}

FileBrowserPage::FileBrowserPage(std::string name, const std::string& path, const std::string& filter, IInputProcessor& inputProcessor) : Page(std::move(name),calculateWindowDimensions(path,filter),inputProcessor) {
    selectedFileIndex = 0;
    directoryPath = std::filesystem::path(path);
    discoveredFiles = FileSystemReader::getDirectoryContents(directoryPath, filter);

    init_color(COLOR_LIGHTBLUE,300,600,1000);
    colour_directory = COLOR_LIGHTBLUE;
    colour_highlightDirectory = COLOR_LIGHTBLUE;
    colour_executable = COLOR_GREEN;
    colour_highlightExecutable = COLOR_GREEN;
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
    if (path.length() > highestLength) {
        highestLength = path.length();
    }

    int width = (int) highestLength + 15;
    int height = (int) fileCount + 6;
    return {width,height};
}

void FileBrowserPage::display() {
    if (!useGlobalColours) {
        init_pair(4,colour_directory,colour_box2);      //BOX_DIRECTORY_COLOUR_PAIR
        init_pair(5,colour_highlightDirectory,colour_boxHighlighted2);  //BOX_HIGHLIGHT_DIRECTORY_COLOUR_PAIR
        init_pair(6,colour_executable,colour_box2);     //BOX_EXECUTABLE_COLOUR_PAIR
        init_pair(7,colour_highlightExecutable,colour_boxHighlighted2); //BOX_HIGHLIGHT_EXECUTABLE_COLOUR_PAIR
    }

    auto currentPath = std::filesystem::current_path();
    mvwprintw(contentWindow,2,4,"./%s",directoryPath.lexically_relative(currentPath).c_str());
    for (int i = 0; i < discoveredFiles.size(); i++) {
        std::string filename = discoveredFiles[i].path().filename();
        bool isDirectory = discoveredFiles[i].is_directory();
        if(selectedFileIndex == i){
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
                int newSelectedEntry = selectedFileIndex - 1;
                if(newSelectedEntry < 0){
                    newSelectedEntry = (int)discoveredFiles.size() - 1;
                }
                selectedFileIndex = newSelectedEntry;
            }
            display();
            break;
        case IInputProcessor::DownKey:
            if (!discoveredFiles.empty()) {
                int newSelectedEntry = selectedFileIndex + 1;
                if(newSelectedEntry >= discoveredFiles.size()){
                    newSelectedEntry = 0;
                }
                selectedFileIndex = newSelectedEntry;
            }
            display();
            break;
        case IInputProcessor::EscapeKey:
            changePageCallback(nullptr);
            break;
        case IInputProcessor::Resize:
            updateSize();
            display();
            break;
        case IInputProcessor::EnterKey:
            std::filesystem::directory_entry& selectedFile = discoveredFiles.at(selectedFileIndex);
            if (selectedFile.is_directory()) {
                if (onSelectDirectory == nullptr) {
                    Logger::appendMessage("'onSelectDirectory' is not set! No action performed for selecting a directory. FileBrowserPage:"+getName());
                } else {
                    (*onSelectDirectory)(selectedFile, this);
                }
            } else if (selectedFile.is_regular_file()) {
                if (onSelectFile == nullptr) {
                    Logger::appendMessage("'onSelectFile' is not set! No action performed for selecting a directory. FileBrowserPage:"+getName());
                } else {
                    (*onSelectFile)(selectedFile, this);
                }
            } else {
                Logger::appendMessage("Non-regular file, unable to process correct action. Path:"+selectedFile.path().string());
                (*onSelectFile)(selectedFile, this);
            }
            break;
    };
}

void FileBrowserPage::setFileBrowserColours(short directory, short highlightDirectory, short executable, short highlightExecutable){
    colour_directory = directory;
    colour_highlightDirectory = highlightDirectory;
    colour_executable = executable;
    colour_highlightExecutable = highlightExecutable;

    init_pair(4,colour_directory,colour_box2);
    init_pair(5,colour_highlightDirectory,colour_boxHighlighted2);
    init_pair(6,colour_executable,colour_box2);
    init_pair(7,colour_highlightExecutable,colour_boxHighlighted2);
}

void FileBrowserPage::setOnSelectDirectory(FileBrowserPage::FileActionCallback *onSelectDirectory) {
    this->onSelectDirectory = onSelectDirectory;
}

void FileBrowserPage::setOnSelectFile(FileBrowserPage::FileActionCallback *onSelectFile) {
    this->onSelectFile = onSelectFile;
}
