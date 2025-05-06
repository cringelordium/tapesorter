#pragma once
#include "ITape.hpp"
#include <string>

class ExternalTapeSorter {
public:
    void sort(ITape& input, ITape& output, size_t memoryLimit);
};