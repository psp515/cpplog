project(cpplog_tests)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


set(CPPLOG_SOURCES
        file_sink_tests.cpp)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest)

function(prepare_test test_target lib)
    add_executable(${test_target} ${CPPLOG_SOURCES})

    target_link_libraries(${test_target} ${lib})
    target_link_libraries(${test_target} GTest::GTest GTest::Main)

    add_test(NAME ${test_target} COMMAND ${test_target})
endfunction()

prepare_test(tests cpplog::cpplog)

