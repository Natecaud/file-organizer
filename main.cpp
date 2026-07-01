#include <iostream>
#include <filesystem>
#include <string>
#include <map>
#include <vector>

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

    std::map<std::string, std::vector<fs::path>> files_by_ext;

    try {
        for (const auto& entry : fs::directory_iterator(target_dir)) {
            if (entry.is_regular_file()) {
                fs::path filepath = entry.path();
                std::string ext = filepath.extension().string();

                // if the file has no extension, use readable lable
                if(ext.empty()) {
                    ext = "(no extension)";
                }

                // add this file to the map under extension key
                files_by_ext[ext].push_back(filepath);
            }
        }
    } catch (const fs::filesystem_error& err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 1;
    }

    // print summary of found files by extension
    std::cout << "\n--- File groups by extension ---\n";
    for (const auto& [ext, files] : files_by_ext) {
        std::cout << " " << ext << ": " << files.size() << " file(s)" << std::endl;
        // list each file
        for (const auto& f : files) {
            std::cout << "   - " << f.filename() << std::endl;
        }
    }

    return 0;
}