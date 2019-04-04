#pragma once
#ifndef SIVOX_GAME_VOXELTERRAIN_HPP
#define SIVOX_GAME_VOXELTERRAIN_HPP

#include "common.hpp"
#include <array>

namespace sivox {
    /*
     * Represents an integer position in the world.
     */
    struct Position {
        int x = 0;
        int y = 0;
        int z = 0;

        Position(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
    };

    inline bool operator==(Position a, Position b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
    inline bool operator!=(Position a, Position b) { return !(a == b); }

    /*
     * Represents a single block in the world.
     */
    struct Block {
        static constexpr int max_id = 1024;

        int id = 0;

        Block() : id(0) {}
        Block(int id_) : id(id_) {}
    };

    inline bool operator==(Block a, Block b) { return a.id == b.id; }
    inline bool operator!=(Block a, Block b) { return !(a == b); }

    /*
     * Represents a small volume of the world.
     */
    class Chunk {
    public:
        static constexpr int width  = 32;
        static constexpr int height = 32;
        static constexpr int volume = width * width * height;

        Block block(Position p) const { 
            if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height && p.z >= 0 && p.z < width) { return m_data[block_index(p)]; }
            else { return 0; }
        }

        void set_block(Position p, Block block) {
            if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height && p.z >= 0 && p.z < width) { m_data[block_index(p)] = block; }
        }

    private:
        std::array<Block, volume> m_data;

        int block_index(Position p) const {
            return p.y + (p.x * height) + (p.z * width * height);
        }
    };
}

#endif // SIVOX_GAME_VOXELTERRAIN_HPP
