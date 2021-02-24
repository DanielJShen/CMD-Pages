//
// Created by Daniel on 21/02/2021.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/Page.h"
#include "../src/BlockingInputProcessor.h"

using ::testing::AtLeast;
using ::testing::Return;

/** The Unique pointer in BlockingInputProcessor should not be moved.
 */
TEST (BlockingInputProcessorTest, CheckUniquePointerNotMoved) {
IInputProcessor& inputProcessor = UseBlockingInputProcessor();
ASSERT_NO_THROW(Page("Page1",{40,10}, inputProcessor).iterate([this](auto &&PH1) {}));
ASSERT_NO_THROW(Page("Page2",{40,10}, inputProcessor).iterate([this](auto &&PH1) {}));
}