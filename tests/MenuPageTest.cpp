//
// Created by Daniel on 16/02/2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/MenuPage.h"
#include "../src/BlockingInputProcessor.h"
#include "MockInputProcessor.h"
#include "MockCallback.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST (MenuPageTest, ClassCreation) {
    ASSERT_NO_THROW(MenuPage("1st Menu", {}, UseBlockingInputProcessor()));
}

TEST (MenuPageTest, InputProcessorCalled) {
    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(1));
    MenuPage initialPage = MenuPage("1st Menu", {}, inputProcessor);
    initialPage.iterate([this](auto &&PH1) {});
}

/** When the escape key is processed by the InputProcessor the callback should be called
 *  with the argument nullptr. This assumes nullptr indicates going back a page.
 */
TEST (MenuPageTest, TestCallback) {
    MockInputProcessor& inputProcessor = UseMockInputProcessor();
    MenuPage initialPage = MenuPage("1st Menu", {}, inputProcessor);
    EXPECT_CALL(inputProcessor, readInput())
            .Times(AtLeast(1))
            .WillOnce(Return(inputProcessor.EscapeKey));
    MockCallback mockCallback;
    EXPECT_CALL(mockCallback, changePage(nullptr))
            .Times(AtLeast(1));
    initialPage.iterate([&mockCallback](auto &&PH1) { mockCallback.changePage(PH1); });
}

/** The Unique pointer in BlockingInputProcessor should not be moved.
 */
TEST (MenuPageTest, CheckUniquePointerNotMoved) {
    IInputProcessor& inputProcessor = UseBlockingInputProcessor();
    ASSERT_NO_THROW(MenuPage("1st Menu", {}, inputProcessor).iterate([this](auto &&PH1) {}));
    ASSERT_NO_THROW(MenuPage("2nd Menu", {}, inputProcessor).iterate([this](auto &&PH1) {}));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}