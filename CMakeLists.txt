# CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

project(genetifex C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(XCB REQUIRED)

add_executable(genetifex main.c genetifex.c screen.c)

target_link_libraries(genetifex
    ${XCB_LIBRARIES}
)

