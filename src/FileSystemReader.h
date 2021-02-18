//
// Created by Daniel on 18/02/2021.
//

#ifndef CMDPAGES_FILESYSTEMREADER_H
#define CMDPAGES_FILESYSTEMREADER_H


#include <vector>
#include <filesystem>

class FileSystemReader {

public:
    static std::vector<std::filesystem::directory_entry> getDirectoryContents(const std::string& path, const std::string& fileFilter);

};


#endif //CMDPAGES_FILESYSTEMREADER_H
