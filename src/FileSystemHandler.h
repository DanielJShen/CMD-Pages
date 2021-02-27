//
// Created by Daniel on 18/02/2021.
//

#ifndef CMDPAGES_FILESYSTEMHANDLER_H
#define CMDPAGES_FILESYSTEMHANDLER_H


#include <vector>
#include <filesystem>

class FileSystemHandler {

public:
    static std::vector<std::filesystem::directory_entry> getDirectoryContents(const std::string& path, const std::string& fileFilter);

    static std::string getFileContent(const std::string &filePath);
    static std::vector<std::string> getFileContentByLines(const std::string &filePath);
    static void createFileIfNotThere(const std::string &filePath);

    static void setFileContent(const std::string& filePath, std::string fileContent);
    static void setFileContent(const std::string &filePath, std::vector<std::string> fileContent);
};


#endif //CMDPAGES_FILESYSTEMHANDLER_H
