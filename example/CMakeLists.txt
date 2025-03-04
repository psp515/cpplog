cmake_minimum_required(VERSION 3.30)

# Add the executable for the example
add_executable(example example.cpp)

# Link the cpplog library to the example
target_link_libraries(example PRIVATE cpplog::cpplog)

