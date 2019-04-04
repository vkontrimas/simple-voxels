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
     * An iterator returned by Chunk::begin and Chunk::end, used to iterate over every block in the chunk.
     * Dereferences to [ChunkIterator::Value] which contains the position and a reference to the block in question.
     */

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

        /*
         * Iterator returned by begin and end used to go through every block in the chunk.
         * Dereferences to a Value type containing the block position and the block itself.
         */
        class Iterator {
        public:
            struct Value {
                Position position;
                Block block;
            };

            Value *operator->() { return nullptr; }
            Value const* operator->() const { return nullptr; }

            Value *operator*() { return nullptr; }
            Value const* operator*() const { return nullptr; }

            Iterator &operator++() { return *this; }
            Iterator operator++(int) { return {}; }

            friend bool operator==(Iterator a, Iterator b);
            friend bool operator!=(Iterator a, Iterator b);
        };

        Iterator begin() { return {}; }
        Iterator end() { return {}; }

    private:
        std::array<Block, volume> m_data;

        int block_index(Position p) const {
            return p.y + (p.x * height) + (p.z * width * height);
        }
    };

    inline bool operator==(Chunk::Iterator a, Chunk::Iterator b) {
        return false;
    }

    inline bool operator!=(Chunk::Iterator a, Chunk::Iterator b) {
        return false;
    }

}

#endif // SIVOX_GAME_VOXELTERRAIN_HPP
