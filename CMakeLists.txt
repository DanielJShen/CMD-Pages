cmake_minimum_required(VERSION 3.12)
project(CMDPages)

set(CMAKE_CXX_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(CMDPages src/main.cpp src/Page.cpp src/ContainerPage.cpp src/Box.cpp src/MenuBox.cpp)
target_link_libraries(CMDPages ${CURSES_LIBRARIES})