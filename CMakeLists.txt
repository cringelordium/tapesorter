cmake_minimum_required(VERSION 3.14)
project(TapeSorter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# основа
add_executable(TapeSorter
    main.cpp
    FileTape.cpp
    ExternalTapeSorter.cpp
)

# генератор и чек
add_executable(GenerateInput tools/generate_input.cpp)
add_executable(CheckSorted tools/check_sorted.cpp)


# gtest
add_subdirectory(external/googletest)
enable_testing()
add_subdirectory(tests)