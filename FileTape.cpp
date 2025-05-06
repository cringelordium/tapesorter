#include "FileTape.hpp"
#include <iostream>

FileTape::FileTape(const std::string& fname, bool writeMode) : filename(fname), position(0) {
    std::ios_base::openmode mode = std::ios::in | std::ios::out | std::ios::binary;
    if (writeMode) mode |= std::ios::trunc;
    file.open(filename, mode);
    if (!file.is_open()) throw std::runtime_error("Failed to open file: " + filename + ". Please try again.");
}

FileTape::~FileTape() {
    file.close();
}

int32_t FileTape::read() {
    int32_t val;
    file.seekg(position * sizeof(int32_t));
    file.read(reinterpret_cast<char*>(&val), sizeof(int32_t));
    return val;
}

void FileTape::write(int32_t value) {
    file.seekp(position * sizeof(int32_t));
    file.write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
    file.flush();
}

void FileTape::moveLeft() {
    if (position > 0) position--;
}

void FileTape::moveRight() {
    position++;
}

bool FileTape::isEOF() const {
    std::streampos targetPos = static_cast<std::streampos>(position * sizeof(int32_t));
    file.seekg(0, std::ios::end);
    std::streampos endPos = file.tellg();

    file.clear(); // сброс флагов после seekg/tellg
    return targetPos >= endPos;
}

void FileTape::rewind() {
    position = 0;
}