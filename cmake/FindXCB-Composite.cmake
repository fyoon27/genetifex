# - Try to find XCB-Composite
# Once done, this will define
#
#  XCB-Composite_FOUND - system has XCB-Composite
#  XCB-Composite_INCLUDE_DIRS - the XCB-Composite include directories
#  XCB-Composite_LIBRARIES - link these to use XCB-Composite

include(LibFindMacros)

libfind_package(XCB-Composite XCB)
libfind_pkg_check_modules(XCB-Composite_PKGCONF xcb-composite)

find_path(XCB-Composite_INCLUDE_DIR
    NAMES xcb/composite.h
    PATHS ${XCB-Composite_PKGCONF_INCLUDE_DIRS}
)

find_library(XCB-Composite_LIBRARY
    NAMES xcb-composite
    PATHS ${XCB-Composite_PKGCONF_LIBRARY_DIRS}
)

set(XCB-Composite_PROCESS_INCLUDES XCB-Composite_INCLUDE_DIR)
set(XCB-Composite_PROCESS_LIBS XCB-Composite_LIBRARY)
libfind_process(XCB-Composite)

