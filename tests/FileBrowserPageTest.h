//
// Created by Daniel on 24/02/2021.
//

#ifndef CMDPAGES_FILEBROWSERPAGETEST_H
#define CMDPAGES_FILEBROWSERPAGETEST_H

class FileBrowserPageTest : public ::testing::Test {
protected:
    void TearDown() override {
        std::filesystem::remove("/tmp/tempCMD_Pages_TempDir/tempCMD_Pages_TempDir");
        std::filesystem::remove("/tmp/tempCMD_Pages_TempDir");
        std::filesystem::remove("/tmp/tempCMD_Pages_FileXXXXX");
        std::filesystem::remove("/tmp/.tempCMD_Pages_FileXXXXX");
    }
};

#endif //CMDPAGES_FILEBROWSERPAGETEST_H
