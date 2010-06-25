# CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

project(genetifex C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_C_FLAGS "-std=c99 -pedantic")

add_definitions(-D_GNU_SOURCE=1)

find_package(XCB REQUIRED)
find_package(XCB-Image REQUIRED)
find_package(XCB-Composite REQUIRED)

add_executable(genetifex
    main.c
    genetifex.c
    screen.c
    player.c
    xpm.c
    timer.c
)

target_link_libraries(genetifex
    ${XCB_LIBRARIES}
    ${XCB-Image_LIBRARIES}
    ${XCB-Composite_LIBRARIES}
    rt
)

