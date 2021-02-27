//
// Created by Daniel on 21/02/2021.
//

#include <fstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/FileSystemHandler.h"
#include "FileSystemHandlerTest.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST_F (FileSystemHandlerTest, MethodRun) {
    ASSERT_NO_THROW(FileSystemHandler::getDirectoryContents(".", ".*"));
}

TEST_F (FileSystemHandlerTest, FindLinuxDirectory) {
    std::vector<std::filesystem::directory_entry> fileList = FileSystemHandler::getDirectoryContents("/", "^usr$");
    ASSERT_TRUE( fileList.size() == 1 );
    ASSERT_TRUE( fileList[0].exists() );
    ASSERT_TRUE( fileList[0].is_directory() );
    ASSERT_TRUE( fileList[0].path().string() == "/usr" );
}

TEST_F (FileSystemHandlerTest, FindLinuxFile) {
    std::ofstream outStream("/tmp/.tempCMD_Pages_FileXXXXX");
    outStream << "Hello, World\nFindLinuxFile Test\n" << std::flush;

    std::vector<std::filesystem::directory_entry> fileList = FileSystemHandler::getDirectoryContents("/tmp/", "^\\.tempCMD_Pages_FileXXXXX");
    ASSERT_EQ( fileList.size(), 1 );
    ASSERT_TRUE( fileList[0].exists() );
    ASSERT_TRUE( fileList[0].is_regular_file() );
    ASSERT_TRUE( fileList[0].path().string() == "/tmp/.tempCMD_Pages_FileXXXXX" );
}

TEST_F (FileSystemHandlerTest, ReadLinuxFile) {
    std::string fileContent = "Hello, World\nReadLinuxFile Test\n";
    std::ofstream outStream("/tmp/.tempCMD_Pages_FileXXXXX");
    outStream << fileContent << std::flush;

    std::string fileOutput = FileSystemHandler::getFileContent("/tmp/.tempCMD_Pages_FileXXXXX");
    ASSERT_EQ( fileOutput, fileContent );
}

TEST_F (FileSystemHandlerTest, CreateLinuxFile) {
    std::string filePath = "/tmp/.tempCMD_Pages_FileXXXXX";

    ASSERT_NO_THROW(FileSystemHandler::createFileIfNotThere(filePath));

    std::vector<std::filesystem::directory_entry> fileList = FileSystemHandler::getDirectoryContents("/tmp/", "^\\.tempCMD_Pages_FileXXXXX");
    ASSERT_EQ( fileList.size(), 1 );
    ASSERT_TRUE( fileList[0].exists() );
    ASSERT_TRUE( fileList[0].is_regular_file() );
    ASSERT_TRUE( fileList[0].path().string() == filePath );
}

TEST_F (FileSystemHandlerTest, DontCreateLinuxFile) {
    std::string filePath = "/tmp/.tempCMD_Pages_FileXXXXX";
    std::string fileContent = "Hello, World\nDontCreateLinuxFile Test\n";
    std::ofstream outStream(filePath);
    outStream << fileContent << std::flush;

    ASSERT_NO_THROW(FileSystemHandler::createFileIfNotThere(filePath));

    std::string fileOutput = FileSystemHandler::getFileContent("/tmp/.tempCMD_Pages_FileXXXXX");
    ASSERT_EQ( fileOutput, fileContent );
}

TEST_F (FileSystemHandlerTest, WriteLinuxFile) {
    std::string fileContent = "Hello, World\nWriteLinuxFile Test\n";
    std::string filePath = "/tmp/.tempCMD_Pages_FileXXXXX";

    FileSystemHandler::createFileIfNotThere(filePath);
    ASSERT_NO_THROW( FileSystemHandler::setFileContent(filePath, fileContent) );
    std::string fileOutput = FileSystemHandler::getFileContent(filePath);
    ASSERT_EQ( fileContent, fileOutput );
}

TEST_F (FileSystemHandlerTest, ReadLinuxFileLines) {
    std::string fileContent = "Hello, World\nReadLinuxFileLines Test\n";
    std::string filePath = "/tmp/.tempCMD_Pages_FileXXXXX";
    std::ofstream outStream(filePath);
    outStream << fileContent << std::flush;

    std::vector<std::string> fileOutput = FileSystemHandler::getFileContentByLines(filePath);
    std::vector<std::string> fileContentLines = {"Hello, World","ReadLinuxFileLines Test",""};
    ASSERT_EQ( fileOutput, fileContentLines );
}

TEST_F (FileSystemHandlerTest, WriteLinuxFileLines) {
    std::vector<std::string> fileContent = {"Hello, World","WriteLinuxFileLines Test",""};
    std::string filePath = "/tmp/.tempCMD_Pages_FileXXXXX";

    FileSystemHandler::createFileIfNotThere(filePath);
    ASSERT_NO_THROW( FileSystemHandler::setFileContent(filePath, fileContent) );
    std::vector<std::string> fileOutput = FileSystemHandler::getFileContentByLines(filePath);
    ASSERT_EQ( fileContent, fileOutput );
}
