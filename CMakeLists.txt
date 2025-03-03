# ---------------------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.30)
project(clog VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)

# ---------------------------------------------------------------------------------------
# Shared Library
# ---------------------------------------------------------------------------------------

set(SRCS src/BaseLogger.cpp)

add_library(clog SHARED
        src/BaseLogger.cpp)

target_compile_definitions(clog PUBLIC CLOG_SHARED_LIB)

add_library(clog::clog ALIAS clog)

# ---------------------------------------------------------------------------------------
# Header Version ??
# ---------------------------------------------------------------------------------------

add_library(clog_header INTERFACE)
add_library(clog::clog_header INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# ---------------------------------------------------------------------------------------
# Build Example
# ---------------------------------------------------------------------------------------

message("Building Example")
add_subdirectory(example)

# ---------------------------------------------------------------------------------------
# Build Test
# ---------------------------------------------------------------------------------------

message("Building Tests")
add_subdirectory(example)

# ---------------------------------------------------------------------------------------
# INSTALL
# ---------------------------------------------------------------------------------------

install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(TARGETS clog spdlog_header_only
        EXPORT clog
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

