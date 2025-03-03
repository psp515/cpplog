cmake_minimum_required(VERSION 3.30)

# Add the executable for the example
add_executable(example example.cpp)

# Link the clog library to the example
target_link_libraries(simple PRIVATE clog::clog)

# Include the parent include directory
target_include_directories(example PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(simple PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)
