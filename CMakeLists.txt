# ---------------------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.30)
project(cpplog VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)

# ---------------------------------------------------------------------------------------
# Shared Library
# ---------------------------------------------------------------------------------------
message("Build Library")

add_library(cpplog SHARED
        src/common/log_event.cpp
        src/logger_configuration.cpp
        src/cpplog.cpp
        src/sinks/stdout_sink.cpp
        src/extensions/formatter.cpp
        src/sinks/file_sink.cpp
        src/sinks/rotation_file_sink.cpp
        include/cpplog/sinks/win_http_sink.h
        src/sinks/win_http_sink.cpp
)

target_compile_definitions(cpplog PUBLIC cpplog_SHARED_LIB)

add_library(cpplog::cpplog ALIAS cpplog)

target_include_directories(cpplog PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_target_properties(cpplog PROPERTIES VERSION 1.0)

# ---------------------------------------------------------------------------------------
# Build Example
# ---------------------------------------------------------------------------------------

message("Building Example")
add_subdirectory(example)

# ---------------------------------------------------------------------------------------
# Build Test
# ---------------------------------------------------------------------------------------

message("Building Tests")
add_subdirectory(tests)

# ---------------------------------------------------------------------------------------
# INSTALL
# ---------------------------------------------------------------------------------------
message("Installing")

install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(TARGETS cpplog
        EXPORT cpplog
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# ---------------------------------------------------------------------------------------
# CMake config files
# ---------------------------------------------------------------------------------------

message("Cmake configuration")
set(project_config_in "${CMAKE_CURRENT_LIST_DIR}/cmake/cpplogConfig.cmake.in")
set(project_config_out "${CMAKE_CURRENT_BINARY_DIR}/cpplogConfig.cmake")
set(config_targets_file "cpplogConfigTargets.cmake")
set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/cpplog")
set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/cpplogConfigVersion.cmake")

include(CMakePackageConfigHelpers)

export(TARGETS cpplog NAMESPACE cpplog::
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${config_targets_file}")
install(EXPORT cpplog DESTINATION ${export_dest_dir} NAMESPACE cpplog:: FILE ${config_targets_file})

include(CMakePackageConfigHelpers)
configure_package_config_file("${project_config_in}" "${project_config_out}" INSTALL_DESTINATION ${export_dest_dir})

write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
install(FILES "${project_config_out}" "${version_config_file}" DESTINATION "${export_dest_dir}")
