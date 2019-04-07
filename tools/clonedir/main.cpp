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

void remove_extras(fs::path const& path, fs::path const& source_dir, fs::path const& target_dir) {
    for (auto const& entry : fs::directory_iterator(path)) {
        fs::path target_path = entry.path();
        fs::path source_path = source_dir / entry.path().lexically_relative(target_dir);

        if (fs::exists(source_path)) {
            if (fs::is_directory(target_path)) {
                if (fs::is_directory(source_path)) {
                    remove_extras(target_path, source_dir, target_dir);
                }
                else {
                    std::cout << "Removing " << target_path << "..." << std::endl;
                    fs::remove_all(target_path);
                }
            }
        }
        else {
            std::cout << "Removing " << target_path << "..." << std::endl;
            fs::remove_all(target_path);
        }
    }
}

int main(int argc, char **argv) {
    if (argc == 3) {
        fs::path source_dir(argv[1]);
        fs::path target_dir(argv[2]);

        bool source_ok = check_dir(source_dir);
        if (source_ok) {
            if (fs::exists(target_dir)) {
                remove_extras(target_dir, source_dir, target_dir);
            }
            fs::copy(
                source_dir, 
                target_dir, 
                fs::copy_options::recursive | 
                fs::copy_options::update_existing |
                fs::copy_options::skip_symlinks
            );
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
