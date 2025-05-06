#include "FileTape.hpp"
#include "ExternalTapeSorter.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " input_file output_file\n";
        return 1;
    }

    try {
        FileTape input(argv[1]);
        FileTape output(argv[2], true);

        ExternalTapeSorter sorter;
        sorter.sort(input, output, 100); // 100 чисел в буфере

        std::cout << "Sorting completed. Niceeee!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}