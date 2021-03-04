//
// Created by Daniel on 04/03/2021.
//

#ifndef CMDPAGES_PAGESCONTROLLERTEST_H
#define CMDPAGES_PAGESCONTROLLERTEST_H

#include <filesystem>

class PagesControllerTest : public ::testing::Test {
protected:
    void TearDown() override {
        std::filesystem::remove("/tmp/.tempCMD_Pages_FileXXXXX");
    }
};

#endif //CMDPAGES_PAGESCONTROLLERTEST_H
