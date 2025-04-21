cmake_minimum_required(VERSION 3.30)

add_executable(example example.cpp
                       http/win_http_sink.cpp)
target_link_libraries(example PRIVATE cpplog::cpplog)

target_link_libraries(example PRIVATE ws2_32)

add_custom_command(TARGET example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/libcpplog.dll
        ${CMAKE_BINARY_DIR}/example/
)
