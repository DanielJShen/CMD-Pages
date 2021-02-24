//
// Created by Daniel on 24/02/2021.
//

#ifndef CMDPAGES_FILESYSTEMREADERTEST_H
#define CMDPAGES_FILESYSTEMREADERTEST_H

class FileSystemReaderTest : public ::testing::Test {
protected:
    void TearDown() override {
        std::filesystem::remove("/tmp/.tempCMD_Pages_FileXXXXX");
    }
};

#endif //CMDPAGES_FILESYSTEMREADERTEST_H
