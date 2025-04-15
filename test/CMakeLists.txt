project(cpplog_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

set(CPPLOG_SOURCES
        common/log_event_tests.cpp)

add_executable(unit_tests ${CPPLOG_SOURCES})

target_link_libraries(unit_tests cpplog)
target_link_libraries(unit_tests gtest gtest_main)

add_test(NAME unit_tests COMMAND unit_tests)

add_custom_command(TARGET unit_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/libcpplog.dll
        ${CMAKE_BINARY_DIR}/tests/
)
