//
// Created by Daniel on 24/02/2021.
//

#include <fstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/FileBrowserPage.h"
#include "../src/BlockingInputProcessor.h"
#include "MockInputProcessor.h"
#include "MockCallback.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST (FileBrowserPageTest, ClassCreation) {
    ASSERT_NO_THROW(FileBrowserPage("1st Menu", ".", UseBlockingInputProcessor()));
}

TEST (FileBrowserPageTest, DirectoryActionCallbackCalled) {
    bool hasCallbackBeenCalled = FALSE;
    typedef std::function<void(const std::filesystem::directory_entry&, FileBrowserPage*)> FileActionCallback;
    FileActionCallback onDirectorySelect = [&hasCallbackBeenCalled]( const std::filesystem::directory_entry& directory, FileBrowserPage* callingObject ) {
        hasCallbackBeenCalled = TRUE;
    };

    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(1))
            .WillOnce(Return(inputProcessor.EnterKey));

    std::filesystem::create_directory("/tmp/tempCMD_Pages_TempDir");

    FileBrowserPage fileBrowserPage = FileBrowserPage("1st Menu", "/tmp", "^tempCMD_Pages_TempDir$", inputProcessor);
    fileBrowserPage.setOnSelectDirectory(&onDirectorySelect);

    fileBrowserPage.iterate([](auto &&PH1) {});
    ASSERT_TRUE(hasCallbackBeenCalled);

    std::filesystem::remove("/tmp/tempCMD_Pages_TempDir");
}

TEST (FileBrowserPageTest, FileActionCallbackCalled) {
    bool hasCallbackBeenCalled = FALSE;
    typedef std::function<void(const std::filesystem::directory_entry&, FileBrowserPage*)> FileActionCallback;
    FileActionCallback onFileSelect = [&hasCallbackBeenCalled]( const std::filesystem::directory_entry& directory, FileBrowserPage* callingObject ) {
        hasCallbackBeenCalled = TRUE;
    };

    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(1))
            .WillOnce(Return(inputProcessor.EnterKey));

    std::ofstream outStream("/tmp/.testFileXXXXX");
    outStream << "Hello, World\n" << std::endl;

    FileBrowserPage fileBrowserPage = FileBrowserPage("1st Menu", "/tmp", "^\\.testFileXXXXX$", inputProcessor);
    fileBrowserPage.setOnSelectDirectory(&onFileSelect);

    fileBrowserPage.iterate([](auto &&PH1) {});
    ASSERT_TRUE(hasCallbackBeenCalled);

    std::remove("/tmp/.testFileXXXXX");
}