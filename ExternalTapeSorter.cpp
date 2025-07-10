#include "ExternalTapeSorter.hpp"
#include "FileTape.hpp"
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <filesystem>

void ExternalTapeSorter::sort(ITape& input, ITape& output, size_t memoryLimit) {
    input.rewind();
    output.rewind();

    std::vector<std::string> tempFiles;

    // std::filesystem::create_directory("tmp");

    // разбиение на отсортированные чанки
    while (!input.isEOF()) {
        std::vector<int32_t> buffer;
        while (buffer.size() < memoryLimit && !input.isEOF()) {
            int32_t value = input.read();
            buffer.push_back(value);
            // std::cout << "Reading: " << value << std::endl;
            input.moveRight();
        }
        std::sort(buffer.begin(), buffer.end());

        std::string tempFile = "/../tmp/chunk_" + std::to_string(tempFiles.size()) + ".bin";
        std::ofstream out(tempFile, std::ios::binary);
        if (!out.is_open()) {
            std::cerr << "Failed to open temp file: " << tempFile << std::endl;
            continue;
        }
        for (int32_t val : buffer)
            out.write(reinterpret_cast<const char*>(&val), sizeof(int32_t));
        tempFiles.push_back(tempFile);
    }

    // слияние чанков
    std::vector<std::ifstream> streams;
    std::vector<int32_t> values;
    std::vector<bool> ended;

    for (const auto& file : tempFiles) {
        std::ifstream in(file, std::ios::binary);
        int32_t val;
        in.read(reinterpret_cast<char*>(&val), sizeof(int32_t));
        streams.push_back(std::move(in));
        values.push_back(val);
        ended.push_back(false);
    }

    while (true) {
        int minIndex = -1;
        for (size_t i = 0; i < streams.size(); ++i) {
            if (!ended[i] && (minIndex == -1 || values[i] < values[minIndex]))
                minIndex = i;
        }
        if (minIndex == -1) break;

        // std::cout << "Writing: " << values[minIndex] << std::endl;
        output.write(values[minIndex]);
        output.moveRight();

        if (!streams[minIndex].read(reinterpret_cast<char*>(&values[minIndex]), sizeof(int32_t)))
            ended[minIndex] = true;
    }

    for (const auto& file : tempFiles)
        std::remove(file.c_str());
}