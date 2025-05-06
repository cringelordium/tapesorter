#pragma once
#include "ITape.hpp"
#include <fstream>
#include <vector>
#include <string>

class FileTape : public ITape {
public:
    FileTape(const std::string& filename, bool writeMode = false);
    ~FileTape();

    int32_t read() override;
    void write(int32_t value) override;
    void moveLeft() override;
    void moveRight() override;
    bool isEOF() const override;
    void rewind() override;

private:
    mutable std::fstream file;
    std::string filename;
    int64_t position;
};
