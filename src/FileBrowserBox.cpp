//
// Created by Daniel on 14/10/2020.
//

#include "FileBrowserBox.h"
#include "Box.h"

#define BOX_HIGHLIGHT_COLOUR_PAIR 1

FileBrowserBox *FileBrowserBox::makeFileBrowserBox(const std::string& name, const std::string& path) {
    return makeFileBrowserBox(name, path, ".*");
}

FileBrowserBox *FileBrowserBox::makeFileBrowserBox(const std::string& name, const std::string& path, const std::string& filter) {
    std::string absolutePath = std::regex_replace(path,std::regex("^\\."),std::filesystem::current_path().string());
    Logger::appendMessage("File Browser - Absolute Path: "+absolutePath);

    int highestLength = 0;
    int fileCount = 0;
    for (auto& entry : std::filesystem::directory_iterator(absolutePath)) {
        if (std::regex_match(entry.path().filename().string(), std::regex(filter) )) {
            int entryLength = entry.path().filename().string().length();
            if (entryLength > highestLength) {
                highestLength = entryLength;
            }
            fileCount++;
        }
    }

    int width = (int) highestLength+15;
    int height = (int) fileCount+6;

    return new FileBrowserBox(width, height, name, absolutePath, filter);
}

FileBrowserBox::FileBrowserBox(int width, int height, const std::string& name, const std::string& path, const std::string& filter) : Box::Box(width, height) {
    boxName = name;
    directoryPath = std::filesystem::path(path);
    fileFilter = filter;
    loadFiles(directoryPath);
}

void FileBrowserBox::display() {
    //mvwprintw(window,0,2,"%s",boxName.c_str());
    mvwprintw(window,2,4,"%s",directoryPath.filename().string().c_str());
    for (int i = 0; i < files.size(); i++) {
        std::string filename = files[i].path().filename();
        bool isDirectory = files[i].is_directory();
        if(selectedFile == i){
            wattron(window,COLOR_PAIR(BOX_HIGHLIGHT_COLOUR_PAIR));
        }
        mvwprintw(window,i+3, 5, "- %s", filename.c_str());
        wattroff(window,COLOR_PAIR(BOX_HIGHLIGHT_COLOUR_PAIR));
    }
    Box::display();
}

void FileBrowserBox::loadFiles(const std::filesystem::path& path) {
    files = {};
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
        Logger::appendMessage("File Browser - File Found: "+entry.path().filename().string()+" Regex Match: "+ std::to_string(std::regex_match(entry.path().filename().string(), std::regex(fileFilter))) );
        if (std::regex_match(entry.path().filename().string(), std::regex(fileFilter) )) {
            files.push_back(entry);
        }
    }
}

/** Triggers an event on the Box
 *
 * @param eventType The event being triggered
 * @param changePageCallback A callback for changing the currently displayed page
 */
void FileBrowserBox::triggerEvent(Box::event eventType, const std::function<void(PagesCore::*)(Page*)> &changePageCallback) {
    switch (eventType) {
        case UpKey:
            if (!files.empty()) {
                int newSelectedEntry = selectedFile - 1;
                if(newSelectedEntry < 0){
                    newSelectedEntry = (int)files.size() - 1;
                }
                selectedFile = newSelectedEntry;
            }
            break;
        case DownKey:
            if (!files.empty()) {
                int newSelectedEntry = selectedFile + 1;
                if(newSelectedEntry >= files.size()){
                    newSelectedEntry = 0;
                }
                selectedFile = newSelectedEntry;
            }
            break;
        case EnterKey:
            //TODO Do action on selection of file
            break;
        case EscapeKey:
            changePageCallback(nullptr);
            break;
    };
}


