#include <gtest/gtest.h>
#include "../FileTape.hpp"
#include <filesystem>

TEST(FileTapeTest, ReadWriteMove) {
    std::filesystem::create_directory("../tmp");
    FileTape tape("../../tmp/test_rw.bin", true);
    tape.write(10);
    tape.moveRight();
    tape.write(20);
    tape.rewind();

    EXPECT_EQ(tape.read(), 10);
    tape.moveRight();
    EXPECT_EQ(tape.read(), 20);
}

TEST(FileTapeTest, MoveLeftAtZeroDoesNothing) {
    FileTape tape("../../tmp/test_left.bin", true);
    tape.write(42);
    tape.moveLeft();  // still at position 0 (bad test need to fix)
    EXPECT_EQ(tape.read(), 42);
}
