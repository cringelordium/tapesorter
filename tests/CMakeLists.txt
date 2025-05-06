add_executable(TapeTests
    tests_tapes.cpp
    tests_sort.cpp
    ../FileTape.cpp
    ../ExternalTapeSorter.cpp
)

target_link_libraries(TapeTests gtest gtest_main pthread)
target_include_directories(TapeTests PRIVATE ${CMAKE_SOURCE_DIR})

add_test(NAME TapeTests COMMAND TapeTests)
