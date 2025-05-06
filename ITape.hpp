#pragma once
#include <cstdint>

class ITape {
public:
    virtual ~ITape() = default;
    virtual int32_t read() = 0;
    virtual void write(int32_t value) = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual bool isEOF() const = 0;
    virtual void rewind() = 0;
};