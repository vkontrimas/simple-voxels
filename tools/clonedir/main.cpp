/*
 * clonedir
 * Cross platform tool to keep directories syncronized.
 * 
 * Usage:
 * clonedir source_dir target_dir
 *
 * Copies the contents of source_dir to target_dir. 
 * If target_dir contains files or directories not present in source_dir, they are deleted.
 */
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

bool check_dir(fs::path const& path) {
    if (!fs::exists(path)) {
        std::cerr << "Path \"" << path << "\" does not exist." << std::endl;
        return false;
    }

    if (!fs::is_directory(path)) {
        std::cerr << "Path " << path << " is not a directory." << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char **argv) {
    if (argc == 3) {
        fs::path source_dir(argv[1]);
        fs::path target_dir(argv[2]);

        bool source_ok = check_dir(source_dir);
        if (source_ok) {
            fs::copy(
                source_dir, 
                target_dir, 
                fs::copy_options::recursive | 
                fs::copy_options::update_existing |
                fs::copy_options::skip_symlinks
            );

            for (auto const& entry : fs::recursive_directory_iterator(target_dir)) {
                fs::path target_path = entry.path();
                fs::path source_path = source_dir / entry.path().lexically_relative(target_dir);

                if (!fs::exists(source_path)) {
                    fs::remove_all(target_path);
                }
            }
        }
        else {
            return 1;
        }
    }
    else {
        std::cerr << "Expected 2 arguments.\nUsage:\nclonedir <source directory> <target directory>" << std::endl;
        return 2;
    }
    return 0;
}
