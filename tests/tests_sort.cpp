#include <gtest/gtest.h>
#include "../FileTape.hpp"
#include "../ExternalTapeSorter.hpp"
#include <vector>
#include <fstream>
#include <filesystem>

void writeToTape(FileTape& tape, const std::vector<int32_t>& data) {
    for (int32_t val : data) {
        tape.write(val);
        tape.moveRight();
    }
    tape.rewind();
}

std::vector<int32_t> readFromTape(FileTape& tape) {
    std::vector<int32_t> result;
    tape.rewind();
    while (!tape.isEOF()) {
        result.push_back(tape.read());
        tape.moveRight();
    }
    return result;
}

TEST(SorterTest, SortsSimpleArray) {
    std::filesystem::create_directory("../tmp");
    FileTape input("../../tmp/input_sort_simple.bin", true);
    FileTape output("../../tmp/output_sort_simple.bin", true);

    writeToTape(input, {5, 2, 4, 3, 1});
    ExternalTapeSorter sorter;
    sorter.sort(input, output, 3);
    auto result = readFromTape(output);

    EXPECT_EQ(result, (std::vector<int32_t>{1, 2, 3, 4, 5}));
}

TEST(SorterTest, HandlesAlreadySorted) {
    FileTape input("../../tmp/input_sorted.bin", true);
    FileTape output("../../tmp/output_sorted.bin", true);

    writeToTape(input, {1, 2, 3, 4, 5});
    ExternalTapeSorter sorter;
    sorter.sort(input, output, 3);
    auto result = readFromTape(output);

    EXPECT_EQ(result, (std::vector<int32_t>{1, 2, 3, 4, 5}));
}

TEST(SorterTest, HandlesDuplicates) {
    FileTape input("../../tmp/input_duplicates.bin", true);
    FileTape output("../../tmp/output_duplicates.bin", true);

    writeToTape(input, {2, 2, 1, 3, 3});
    ExternalTapeSorter sorter;
    sorter.sort(input, output, 2);
    auto result = readFromTape(output);

    EXPECT_EQ(result, (std::vector<int32_t>{1, 2, 2, 3, 3}));
}

TEST(SorterTest, HandlesSingleElement) {
    FileTape input("../../tmp/input_single.bin", true);
    FileTape output("../../tmp/output_single.bin", true);

    writeToTape(input, {42});
    ExternalTapeSorter sorter;
    sorter.sort(input, output, 1);
    auto result = readFromTape(output);

    EXPECT_EQ(result, (std::vector<int32_t>{42}));
}

TEST(SorterTest, HandlesEmptyInput) {
    FileTape input("../../tmp/input_empty.bin", true);
    FileTape output("../../tmp/output_empty.bin", true);

    ExternalTapeSorter sorter;
    sorter.sort(input, output, 10);
    auto result = readFromTape(output);

    EXPECT_TRUE(result.empty());
}