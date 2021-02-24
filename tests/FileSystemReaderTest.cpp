//
// Created by Daniel on 21/02/2021.
//

#include <fstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/FileSystemReader.h"
#include "FileSystemReaderTest.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST_F (FileSystemReaderTest, MethodRun) {
    ASSERT_NO_THROW(FileSystemReader::getDirectoryContents(".",".*"));
}

TEST_F (FileSystemReaderTest, FindLinuxDirectory) {
    std::vector<std::filesystem::directory_entry> fileList = FileSystemReader::getDirectoryContents("/","^usr$");
    ASSERT_TRUE( fileList.size() == 1 );
    ASSERT_TRUE( fileList[0].exists() );
    ASSERT_TRUE( fileList[0].is_directory() );
    ASSERT_TRUE( fileList[0].path().string() == "/usr" );
}

TEST_F (FileSystemReaderTest, FindLinuxFile) {
    std::ofstream outStream("/tmp/.tempCMD_Pages_FileXXXXX");
    outStream << "Hello, World\n" << std::endl;

    std::vector<std::filesystem::directory_entry> fileList = FileSystemReader::getDirectoryContents("/tmp/","^\\.tempCMD_Pages_FileXXXXX");
    ASSERT_EQ( fileList.size(), 1 );
    ASSERT_TRUE( fileList[0].exists() );
    ASSERT_TRUE( fileList[0].is_regular_file() );
    ASSERT_TRUE( fileList[0].path().string() == "/tmp/.tempCMD_Pages_FileXXXXX" );
}