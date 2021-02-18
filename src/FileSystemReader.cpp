//
// Created by Daniel on 18/02/2021.
//

#include <regex>
#include "FileSystemReader.h"
#include "Logger.h"

std::vector<std::filesystem::directory_entry> FileSystemReader::getDirectoryContents(const std::string& path, const std::string& fileFilter) {
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