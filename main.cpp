#include <iostream>
#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <cstring> // for strcmp

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    // check for --dry-run flag
    bool dry_run = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--dry-run") == 0) {
            dry_run = true;
            break;
        }
    }

    // determines the target directory (skips --dry-run arg)
    fs::path target_dir = fs::current_path();
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--dry-run") != 0) {
            target_dir = argv[i];
            break;
        }
    }

    if (dry_run) {
        std::cout << "[DRY RUN] No files will be moved.\n";
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

    // process each extension group
    for (const auto& [ext, files] : files_by_ext) {
        if (ext == "(no extension)") {
            continue; // skip files without extensions
        }

        std::string folder_name = ext.substr(1); //remove leading dot
        fs::path subfolder = target_dir / folder_name;

        // create folder if needed (unless dry run)
        if (!fs::exists(subfolder)) {
            if (!dry_run) {
                fs::create_directory(subfolder);
                std::cout << "Created folder: " << subfolder << std::endl;
            } else {
                std::cout << "[DRY RUN] Would create folder: " << subfolder << std::endl;
            }
        }

        for (const auto& filepath : files) {
            fs::path dest = subfolder / filepath.filename();
            if (!dry_run) {
                fs::rename(filepath, dest);
                std::cout << " Moved: " << filepath.filename() << " -> " << dest << std::endl;
            } else {
                std::cout << " [DRY RUN] Would move: " << filepath.filename() << " -> " << dest << std::endl;
            }
        }
    }

    return 0;
}