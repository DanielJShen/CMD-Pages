cmake_minimum_required(VERSION 3.12)
project(CMDPages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCES src/Page.h src/Page.cpp src/FileBrowserPage.h src/FileBrowserPage.cpp src/MenuPage.h src/MenuPage.cpp src/Logger.h src/Logger.cpp src/PagesDisplayLoop.h src/PagesDisplayLoop.cpp src/UUIDGenerator.cpp src/UUIDGenerator.h src/FileSystemReader.cpp src/FileSystemReader.h src/IInputProcessor.h src/BlockingInputProcessor.cpp src/BlockingInputProcessor.h)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
        ${PROJECT_NAME}_lib
        ${CURSES_LIBRARIES}
        stdc++fs)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(${PROJECT_NAME}Test tests/MenuPageTest.cpp )
target_link_libraries(${PROJECT_NAME}Test
        ${PROJECT_NAME}_lib
        ${CURSES_LIBRARIES}
        stdc++fs
        GTest::GTest
        GTest::Main)
include_directories($ENV{GMOCK_HOME}/googlemock/include)
include_directories($ENV{GMOCK_HOME}/googletest/include)
gtest_discover_tests(${PROJECT_NAME}Test)