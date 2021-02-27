//
// Created by Daniel on 24/02/2021.
//

#include <fstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/FileBrowserPage.h"
#include "../src/InputHandling/BlockingInputProcessor.h"
#include "MockInputProcessor.h"
#include "FileBrowserPageTest.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST_F (FileBrowserPageTest, ClassCreation) {
    ASSERT_NO_THROW(FileBrowserPage("1st Menu", ".", UseBlockingInputProcessor()));
}

TEST_F (FileBrowserPageTest, DirectoryActionCallbackCalled) {
    bool hasCallbackBeenCalled = FALSE;
    typedef std::function<void(const std::filesystem::directory_entry&, FileBrowserPage*)> FileActionCallback;
    FileActionCallback onDirectorySelect = [&hasCallbackBeenCalled]( const std::filesystem::directory_entry& directory, FileBrowserPage* callingObject ) {
        hasCallbackBeenCalled = TRUE;
    };

    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(1))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::EnterKey) ));

    std::filesystem::create_directory("/tmp/tempCMD_Pages_TempDir");

    FileBrowserPage fileBrowserPage = FileBrowserPage("1st Menu", "/tmp", "^tempCMD_Pages_TempDir$", inputProcessor);
    fileBrowserPage.setOnSelectDirectory(&onDirectorySelect);

    fileBrowserPage.iterate([](auto &&PH1) {});
    ASSERT_TRUE(hasCallbackBeenCalled);
}

TEST_F (FileBrowserPageTest, FileActionCallbackCalled) {
    bool hasCallbackBeenCalled = FALSE;
    typedef std::function<void(const std::filesystem::directory_entry&, FileBrowserPage*)> FileActionCallback;
    FileActionCallback onFileSelect = [&hasCallbackBeenCalled]( const std::filesystem::directory_entry& directory, FileBrowserPage* callingObject ) {
        hasCallbackBeenCalled = TRUE;
    };

    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(1))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::EnterKey) ));

    std::ofstream outStream("/tmp/.tempCMD_Pages_FileXXXXX");
    outStream << "Hello, World\n" << std::endl;

    FileBrowserPage fileBrowserPage = FileBrowserPage("1st Menu", "/tmp", "^\\.tempCMD_Pages_FileXXXXX$", inputProcessor);
    fileBrowserPage.setOnSelectFile(&onFileSelect);

    fileBrowserPage.iterate([](auto &&PH1) {});
    ASSERT_TRUE(hasCallbackBeenCalled);
}

TEST_F (FileBrowserPageTest, SubdirectoriesDirectoryActionCalled) {
    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(2))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::EnterKey) ))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::EnterKey) ));

    std::filesystem::create_directory("/tmp/tempCMD_Pages_TempDir");
    std::filesystem::create_directory("/tmp/tempCMD_Pages_TempDir/tempCMD_Pages_TempDir");

    FileBrowserPage fileBrowserPage = FileBrowserPage("1st Menu", "/tmp", "^tempCMD_Pages_TempDir$", inputProcessor);

    bool hasCallbackBeenCalled = FALSE;
    std::vector<std::shared_ptr<FileBrowserPage>> fileBrowserPagePointers;
    typedef std::function<void(const std::filesystem::directory_entry&, FileBrowserPage*)> FileActionCallback;
    FileActionCallback onDirectorySelect = [&hasCallbackBeenCalled,&fileBrowserPagePointers,&onDirectorySelect,&inputProcessor]( const std::filesystem::directory_entry& directory, FileBrowserPage* callingObject ) {
        std::shared_ptr<FileBrowserPage> fileBrowserPagePtr = std::make_unique<FileBrowserPage>(callingObject->getName(), directory.path(),"^tempCMD_Pages_TempDir$", inputProcessor);
        fileBrowserPagePtr->setOnSelectDirectory(&onDirectorySelect);
        fileBrowserPagePointers.push_back(fileBrowserPagePtr);
        hasCallbackBeenCalled = TRUE;
    };
    fileBrowserPage.setOnSelectDirectory(&onDirectorySelect);

    fileBrowserPage.iterate([](auto &&PH1) {});
    ASSERT_TRUE(hasCallbackBeenCalled);
    hasCallbackBeenCalled = FALSE;
    fileBrowserPagePointers.back()->iterate([](auto &&PH1) {});
    ASSERT_TRUE(hasCallbackBeenCalled);
    ASSERT_EQ(fileBrowserPagePointers.size(),2);
}