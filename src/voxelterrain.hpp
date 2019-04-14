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
        static constexpr int length = 32;
        static constexpr int volume = width * length * height;

        Block block(Position p) const { 
            if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height && p.z >= 0 && p.z < length) { return m_data[block_index(p)]; }
            else { return 0; }
        }

        void set_block(Position p, Block block) {
            if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height && p.z >= 0 && p.z < length) { m_data[block_index(p)] = block; }
        }

        /*
         * Iterator returned by begin and end used to go through every block in the chunk.
         * Dereferences to a Value type containing the block position and the block itself.
         * This iterator is pretty much read only.
         */
        class Iterator {
        public:
            // TODO: Should we make the fields in Chunk::Iterator::Value const?
            struct Value {
                Position position;
                Block block;
            };

            Iterator(std::array<Block, volume> const* data, int pos) : m_data(data), m_position(pos) {}

            Value operator->() const { 
                return {
                    block_position(m_position),
                    (*m_data)[m_position]
                };
            }

            Value operator*() const { 
                return {
                    block_position(m_position),
                    (*m_data)[m_position]
                };
            }

            Iterator &operator++() { 
                m_position++;
                return *this; 
            }

            Iterator operator++(int) { 
                m_position++;
                return *this;
            }

            friend bool operator==(Iterator a, Iterator b) {
                return a.m_data && b.m_data && a.m_position == b.m_position && a.m_data == b.m_data;
            }

            friend bool operator!=(Iterator a, Iterator b) {
                return !(a == b);
            }

        private:
            std::array<Block, volume> const* m_data;
            int m_position;
        };

        Iterator begin() const { return Iterator(&m_data, 0); }
        Iterator end() const { return Iterator(&m_data, volume); }

    private:
        std::array<Block, volume> m_data;

        static int block_index(Position p) {
            return p.y + (p.x * height) + (p.z * width * height);
        }

        static Position block_position(int index) {
            int y = (index % (width * height)) % height;
            int x = ((index % (width * height)) - y) / height;
            int z = (index - x - y) / (width * height);
            return {x, y, z};
        }
    };
}

#endif // SIVOX_GAME_VOXELTERRAIN_HPP
