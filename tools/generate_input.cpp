#include <fstream>
#include <iostream>
#include <random>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " output_file num_elements\n";
        return 1;
    }

    std::string filename = argv[1];
    int n = std::stoi(argv[2]);

    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return 1;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int32_t> dist(-10000, 10000);

    for (int i = 0; i < n; ++i) {
        int32_t val = dist(rng);
        out.write(reinterpret_cast<const char*>(&val), sizeof(int32_t));
    }

    std::cout << "Generated " << n << " integers to " << filename << "\n";
    return 0;
}
