#pragma once
#ifndef SIVOX_GAME_IOUTILS_HPP
#define SIVOX_GAME_IOUTILS_HPP

#include <string>

namespace sivox {
    std::string read_text_file(std::string const& path);
    void write_text_file(std::string const& path, std::string const& contents);
}

#endif // SIVOX_GAME_IOUTILS_HPP
