#include "ioutils.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace sivox {
    std::string read_text_file(fs::path const& path) {
        if (fs::exists(path) && fs::is_regular_file(path)) {
            std::ifstream file(path);

            file.seekg(0, file.end);
            auto length = file.tellg();
            file.seekg(0, file.beg);

            std::string text(length, ' ');
            file.read(&text[0], length);

            return text;
        }
        else {
            return "";
        }
    }

    void write_text_file(fs::path const& path, std::string const& contents) {
        std::ofstream file(path);
        file << contents;
    }
}
