//
// Created by Daniel on 16/02/2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/Page.h"
#include "../src/InputHandling/BlockingInputProcessor.h"
#include "MockInputProcessor.h"
#include "MockCallback.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST (PageTest, ClassCreation) {
    ASSERT_NO_THROW(Page("Page", {40,10}, UseBlockingInputProcessor()));
}

TEST (PageTest, InputProcessorCalled) {
    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(1));
    Page initialPage = Page("Page", {40,10}, inputProcessor);
    initialPage.iterate([this](auto &&PH1) {});
}

/** When the escape key is processed by the InputProcessor the callback should be called
 *  with the argument nullptr. This assumes nullptr indicates going back a page.
 */
TEST (PageTest, TestCallback) {
    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    Page initialPage = Page("Page", {40,10}, inputProcessor);
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(1))
            .WillOnce(Return(KeyInput(KeyInput::inputEvent::EscapeKey)));

    MockCallback mockCallback;
    EXPECT_CALL(mockCallback, changePage(nullptr))
            .Times(AtLeast(1));
    initialPage.iterate([&mockCallback](auto &&PH1) { mockCallback.changePage(PH1); });
}

/** The callback should only be called when the EscapeKey is pressed
 */
TEST (PageTest, TestNoCallback) {
    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    Page initialPage = Page("Page", {40,10}, inputProcessor);
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(7))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::RightKey) ))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::LeftKey) ))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::UpKey) ))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::DownKey) ))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::EnterKey) ))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::Resize) ))
            .WillOnce(Return( KeyInput(KeyInput::inputEvent::NoAction) ));
    for (int i=0; i<7; i++) {
        initialPage.iterate([this](auto &&PH1) { ASSERT_TRUE(FALSE); });
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}