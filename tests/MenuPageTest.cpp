//
// Created by Daniel on 16/02/2021.
//

#include "gtest/gtest.h"
#include "../src/MenuPage.h"

TEST (MenuPageTest, ClassCreation) {
    ASSERT_NO_FATAL_FAILURE(MenuPage("1st Menu", {}));
}

TEST (MenuPageTest, KeyInput) {
    MenuPage initialPage = MenuPage("1st Menu", {});
    initialPage.iterate([this](auto &&PH1) { ASSERT_TRUE(PH1 == nullptr); });
    //TODO Fake key input
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}