//
// Created by Daniel on 18/02/2021.
//

#include <regex>
#include <fstream>
#include "FileSystemHandler.h"
#include "Logger.h"

std::vector<std::filesystem::directory_entry> FileSystemHandler::getDirectoryContents(const std::string& path, const std::string& fileFilter) {
    std::string absolutePath = std::regex_replace(path,std::regex("^\\.$"),std::filesystem::current_path().string());
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

std::string FileSystemHandler::getFileContent(const std::string &filePath) {
    std::ifstream fileInputStream(filePath, std::ios::in | std::ios::binary);
    const auto fileSize = std::filesystem::file_size(filePath);
    std::string fileBuffer(fileSize, '\0');

    fileInputStream.read(fileBuffer.data(), fileSize);
    return fileBuffer;
}

std::vector<std::string> FileSystemHandler::getFileContentByLines(const std::string &filePath) {
    std::string fileString = FileSystemHandler::getFileContent(filePath);
    std::vector<std::string> stringVector = std::vector<std::string>();
    std::string currentLine;
    for (char charachter : fileString) {
        if (charachter == '\n') {
            stringVector.push_back(currentLine);
            currentLine.clear();
        } else {
            currentLine += charachter;
        }
    }
    stringVector.push_back(currentLine);
    return stringVector;
}

void FileSystemHandler::createFileIfNotThere(const std::string &filePath) {
    std::filesystem::path path(filePath);
    if (! std::filesystem::exists(path)) {
        Logger::appendMessage(
                "Creating file: " + path.filename().string() + " at path: " + path.parent_path().string());
        std::filesystem::create_directories(path.parent_path());

        std::ofstream ofs(path);
        ofs.close();
    }
}