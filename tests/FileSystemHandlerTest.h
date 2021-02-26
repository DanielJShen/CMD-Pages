//
// Created by Daniel on 24/02/2021.
//

#ifndef CMDPAGES_FILESYSTEMHANDLERTEST_H
#define CMDPAGES_FILESYSTEMHANDLERTEST_H

class FileSystemHandlerTest : public ::testing::Test {
protected:
    void TearDown() override {
        std::filesystem::remove("/tmp/.tempCMD_Pages_FileXXXXX");
    }
};

#endif //CMDPAGES_FILESYSTEMHANDLERTEST_H
