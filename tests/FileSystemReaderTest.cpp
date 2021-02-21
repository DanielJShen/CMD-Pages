//
// Created by Daniel on 21/02/2021.
//

#include <fstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/FileSystemReader.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST (PageTest, MethodRun) {
    ASSERT_NO_THROW(FileSystemReader::getDirectoryContents(".",".*"));
}

TEST (PageTest, FindLinuxDirectory) {
    std::vector<std::filesystem::directory_entry> fileList = FileSystemReader::getDirectoryContents("/","^usr$");
    ASSERT_TRUE( fileList.size() == 1 );
    ASSERT_TRUE( fileList[0].exists() );
    ASSERT_TRUE( fileList[0].is_directory() );
    ASSERT_TRUE( fileList[0].path().string() == "/usr" );
}

TEST (PageTest, FindLinuxFile) {
    std::ofstream outStream("/tmp/.testFileXXXXX");
    outStream << "Hello, World\n" << std::endl;

    std::vector<std::filesystem::directory_entry> fileList = FileSystemReader::getDirectoryContents("/tmp/","^\\.testFileXXXXX$");
    ASSERT_EQ( fileList.size(), 1 );
    ASSERT_TRUE( fileList[0].exists() );
    ASSERT_TRUE( fileList[0].is_regular_file() );
    ASSERT_TRUE( fileList[0].path().string() == "/tmp/.testFileXXXXX" );
    std::remove("/tmp/.testFileXXXXX");
}