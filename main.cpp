#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    //determines the target directory
    fs::path target_dir;
    if (argc > 1) {
        target_dir = argv[1];
    } else {
        target_dir = fs::current_path();
    }

    std::cout << "Scanning directory: " << target_dir << std::endl;

    try {
        for (const auto& entry : fs::directory_iterator(target_dir)) {
            //only processes regular files, ignores subdirectories and weird things
            if (entry.is_regular_file()) {
                std::cout << "Found file: " << entry.path().filename() << std::endl;
            }
        }
    } catch (const fs::filesystem_error& err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 1;
    }
    
    return 0;
}