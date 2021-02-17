cmake_minimum_required(VERSION 3.12)
project(CMDPages)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(CMDPages src/main.cpp src/Page.h src/Page.cpp src/FileBrowserPage.h src/FileBrowserPage.cpp src/MenuPage.h src/MenuPage.cpp src/Logger.h src/Logger.cpp src/PagesDisplayLoop.h src/PagesDisplayLoop.cpp src/UUIDGenerator.cpp src/UUIDGenerator.h)
target_link_libraries(CMDPages ${CURSES_LIBRARIES} stdc++fs)