//
// Created by Daniel on 14/10/2020.
//

#include "FileBrowserPage.h"
#include "FileSystemHandler.h"
#include "InputHandling/BlockingInputProcessor.h"
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

FileBrowserPage::FileBrowserPage(std::string name, const std::string &path, IInputProcessor &inputProcessor)
        : FileBrowserPage(std::move(name), path, ".*", inputProcessor) {
}

FileBrowserPage::FileBrowserPage(std::string name, const std::string &path, const std::string &filter, IInputProcessor &inputProcessor)
        : Page(std::move(name), calculateWindowDimensions(name,path,filter),inputProcessor) {
    selectedFileIndex = 0;
    directoryPath = std::filesystem::path(path);
    discoveredFiles = FileSystemHandler::getDirectoryContents(directoryPath, filter);

    init_color(COLOR_LIGHTBLUE,300,600,1000);
    colour_directory = COLOR_LIGHTBLUE;
    colour_highlightDirectory = COLOR_LIGHTBLUE;
    colour_executable = COLOR_GREEN;
    colour_highlightExecutable = COLOR_GREEN;
}

std::array<int, 2> FileBrowserPage::calculateWindowDimensions(const std::string& name, const std::string& path, const std::string& filter) {
    std::vector<std::filesystem::directory_entry> files = FileSystemHandler::getDirectoryContents(path, filter);

    int highestLength = (int) name.length();
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

void FileBrowserPage::displayContent() {
    if (!useGlobalColours) {
        init_pair(4,colour_directory,colour_box2);      //BOX_DIRECTORY_COLOUR_PAIR
        init_pair(5,colour_highlightDirectory,colour_boxHighlighted2);  //BOX_HIGHLIGHT_DIRECTORY_COLOUR_PAIR
        init_pair(6,colour_executable,colour_box2);     //BOX_EXECUTABLE_COLOUR_PAIR
        init_pair(7,colour_highlightExecutable,colour_boxHighlighted2); //BOX_HIGHLIGHT_EXECUTABLE_COLOUR_PAIR
    }

    auto currentPath = std::filesystem::current_path();
    std::string stringPath = directoryPath.lexically_relative(currentPath).string();
    if (stringPath.find("../") != std::string::npos) {
        mvwprintw(contentWindow, 2, 4, "%s", directoryPath.c_str());
    } else {
        mvwprintw(contentWindow, 2, 4, "./%s", stringPath.c_str());
    }
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
    Page::displayContent();
}

void FileBrowserPage::updateSize(int windowWidth, int windowHeight) {
    Page::updateSize(windowWidth, windowHeight);
}

void FileBrowserPage::updateSize() {
    Page::updateSize();
}

void FileBrowserPage::triggerEvent(const PageCallback &changePageCallback, KeyInput keyInput) {
    if (keyInput.getObjectInputType() == KeyInput::inputType::functionKey) {
        switch (keyInput.getFunctionKeyInput()) {
            case KeyInput::UpKey:
                if (!discoveredFiles.empty()) {
                    int newSelectedEntry = selectedFileIndex - 1;
                    if (newSelectedEntry < 0) {
                        newSelectedEntry = (int) discoveredFiles.size() - 1;
                    }
                    selectedFileIndex = newSelectedEntry;
                }
                displayContent();
                break;
            case KeyInput::DownKey:
                if (!discoveredFiles.empty()) {
                    int newSelectedEntry = selectedFileIndex + 1;
                    if (newSelectedEntry >= discoveredFiles.size()) {
                        newSelectedEntry = 0;
                    }
                    selectedFileIndex = newSelectedEntry;
                }
                displayContent();
                break;
            case KeyInput::EscapeKey:
                changePageCallback(nullptr);
                break;
            case KeyInput::Resize:
                updateSize();
                displayContent();
                break;
            case KeyInput::EnterKey:
                if (!discoveredFiles.empty()) {
                    std::filesystem::directory_entry &selectedFile = discoveredFiles.at(selectedFileIndex);
                    if (selectedFile.is_directory()) {
                        if (onSelectDirectory == nullptr) {
                            Logger::appendMessage(
                                    "'onSelectDirectory' is not set! No action performed for selecting a directory. FileBrowserPage:" +
                                    getName());
                        } else {
                            (*onSelectDirectory)(selectedFile, this);
                        }
                    } else if (selectedFile.is_regular_file()) {
                        if (onSelectFile == nullptr) {
                            Logger::appendMessage(
                                    "'onSelectFile' is not set! No action performed for selecting a directory. FileBrowserPage:" +
                                    getName());
                        } else {
                            (*onSelectFile)(selectedFile, this);
                        }
                    } else {
                        Logger::appendMessage(
                                "Non-regular file, unable to process correct action. Path:" +
                                selectedFile.path().string());
                        (*onSelectFile)(selectedFile, this);
                    }
                }
                break;
        };
    }
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
