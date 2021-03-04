//
// Created by Daniel on 04/03/2021.
//
#include <fstream>
#include "gtest/gtest.h"
#include "../src/PagesController.h"
#include "PagesControllerTest.h"


TEST_F (PagesControllerTest, RunCommand) {
    ASSERT_NO_THROW( PagesController::executeExternalLinuxCommand("echo -n") );
}

TEST_F (PagesControllerTest, ReadLinuxFileWithCommand) {
    std::string fileContent = "Hello, World\nReadLinuxFile Test\n";
    std::ofstream outStream("/tmp/.tempCMD_Pages_FileXXXXX");
    outStream << fileContent << std::flush;

    std::string fileOutput = PagesController::executeLinuxCommand("cat /tmp/.tempCMD_Pages_FileXXXXX");
    ASSERT_EQ( fileOutput, fileContent );
}
