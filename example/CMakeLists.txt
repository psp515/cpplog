cmake_minimum_required(VERSION 3.30)

# Optionally, ensure that cpplog is built as a shared library
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)

# Add the executable for the example
add_executable(example example.cpp)

# Link the cpplog shared library to the example
target_link_libraries(example PRIVATE cpplog::cpplog)

# Post-build command to copy the cpplog.dll to the example output directory
add_custom_command(TARGET example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/libcpplog.dll
        ${CMAKE_BINARY_DIR}/example/
)
