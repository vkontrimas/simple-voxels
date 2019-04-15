#pragma once
#ifndef SIVOX_GAME_VOXELTERRAIN_HPP
#define SIVOX_GAME_VOXELTERRAIN_HPP

#include "common.hpp"
#include <array>
#include <unordered_map>
#include <memory>

namespace sivox {
    /*
     * Represents an integer position in the world.
     *
     * TODO: Rename to Vec3i or something. This is specifically for voxel terrain though,
     * so maybe something more voxel-y..?
     *                                                                  - vk 15/04/2019
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
        static constexpr int width_bits = 5;
        static constexpr int height_bits = 5;
        static constexpr int length_bits = 5;

        // NOTE: Not sure if (width|height|length)_bits == 0 would work?
        static_assert(width_bits > 0);
        static_assert(height_bits > 0);
        static_assert(length_bits > 0);
        static_assert(width_bits + height_bits + length_bits <= 32);

        static constexpr int width  = 1 << width_bits;
        static constexpr int height = 1 << height_bits;
        static constexpr int length = 1 << length_bits;
        static constexpr int volume = width * length * height;

        static constexpr int width_mask = width - 1;
        static constexpr int height_mask = height - 1;
        static constexpr int length_mask = length - 1;

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
            auto index = p.y & height_mask;
            index |= (p.x & width_mask) << height_bits;
            index |= (p.z & length_mask) << (height_bits + width_bits);
            return index;
        }

        static Position block_position(int index) {
            int x = (index >> height_bits) & width_mask;
            int y = index & height_mask;
            int z = (index >> (height_bits + width_bits)) & length_mask;
            return {x, y, z};
        }
    };

    class Terrain {
    public:
        Terrain(int width_chunks, int height_chunks, int length_chunks) {}

        int width_chunks() const { return m_width_chunks; }
        int height_chunks() const { return m_height_chunks; }
        int length_chunks() const { return m_length_chunks; }
        int volume_chunks() const { return width_chunks() * height_chunks() * length_chunks(); }

        int width_blocks() const { return width_chunks() * Chunk::width; }
        int height_blocks() const { return height_chunks() * Chunk::height; }
        int length_blocks() const { return length_chunks() * Chunk::length; }
        int volume_blocks() const { return width_blocks() * height_blocks() * length_blocks(); }

        Chunk *chunk(Position chunk_position) { return nullptr; }
        Chunk const* chunk(Position chunk_position) const { return nullptr; }

        Chunk *create_chunk(Position chunk_position) { return nullptr; }
        void delete_chunk(Position chunk_position) {}

    private:
        std::unordered_map<int, std::unique_ptr<Chunk>> m_chunks;
        int m_width_chunks, m_height_chunks, m_length_chunks;
    };
}

#endif // SIVOX_GAME_VOXELTERRAIN_HPP
