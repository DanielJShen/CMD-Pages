//
// Created by Daniel on 16/02/2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/MenuPage.h"
#include "../src/BlockingInputProcessor.h"
#include "MockInputProcessor.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST (MenuPageTest, ClassCreation) {
    ASSERT_NO_FATAL_FAILURE(MenuPage("1st Menu", {}, UseBlockingInputProcessor()));
}

bool hasCallbackBeenCalled = FALSE;

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
    initialPage.iterate([this](auto &&PH1) { hasCallbackBeenCalled = TRUE; ASSERT_TRUE(PH1 == nullptr); });
    ASSERT_TRUE(hasCallbackBeenCalled);
    hasCallbackBeenCalled = FALSE;
}

/** The Unique pointer in BlockingInputProcessor should not be moved.
 */
TEST (MenuPageTest, CheckUniquePointerNotMoved) {
    IInputProcessor& inputProcessor = UseBlockingInputProcessor();
    ASSERT_NO_FATAL_FAILURE(Page("1st Menu",{40,10}, inputProcessor).iterate([this](auto &&PH1) {}));
    ASSERT_NO_FATAL_FAILURE(Page("1st Menu",{40,10}, inputProcessor).iterate([this](auto &&PH1) {}));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PainterTest, CanDrawSomething) {
}