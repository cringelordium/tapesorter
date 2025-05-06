#include <fstream>
#include <iostream>
#include <cstdint>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " sorted_file\n";
        return 1;
    }

    std::ifstream in(argv[1], std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }

    int32_t prev, curr;
    if (!in.read(reinterpret_cast<char*>(&prev), sizeof(int32_t))) {
        std::cout << "File is empty, considered sorted.\n";
        return 0;
    }

    size_t index = 1;
    while (in.read(reinterpret_cast<char*>(&curr), sizeof(int32_t))) {
        if (curr < prev) {
            std::cerr << "Not sorted at index " << index << ": "
                      << prev << " > " << curr << "\n";
            return 1;
        }
        prev = curr;
        ++index;
    }

    std::cout << "File is correctly sorted.\n";
    return 0;
}