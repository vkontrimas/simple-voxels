#pragma once
#ifndef SIVOX_GAME_VOXELTERRAIN_HPP
#define SIVOX_GAME_VOXELTERRAIN_HPP

#include "common.hpp"
#include <array>
#include <vector>
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>

namespace sivox {
    /*
     * Represents an integer position in the world.
     *
     * TODO: Rename to Vec3i or something. This is specifically for voxel terrain though,
     * so maybe something more voxel-y..?
     *                                                                  - vk 15/04/2019
     */
    struct Position {
        s32 x = 0;
        s32 y = 0;
        s32 z = 0;

        Position() : x(0), y(0), z(0) {}
        Position(s32 x_, s32 y_, s32 z_) : x(x_), y(y_), z(z_) {}

        /*
         * Returns the chunk position of the chunk the block at [position] is located in.
         */
        static Position block_to_chunk(Position position); 

        static float distance(Position a, Position b) {
            float dx = a.x - b.x;
            float dy = a.y - b.y;
            float dz = a.z - b.z;
            return glm::sqrt(dx * dx + dy * dy + dz * dz);
        }
    };

    inline bool operator==(Position a, Position b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
    inline bool operator!=(Position a, Position b) { return !(a == b); }

    /*
     * Represents a single block in the world.
     */
    struct Block {
        static constexpr s32 max_id = 1024;

        s32 id = 0;

        Block() : id(0) {}
        Block(s32 id_) : id(id_) {}
    };

    inline bool operator==(Block a, Block b) { return a.id == b.id; }
    inline bool operator!=(Block a, Block b) { return !(a == b); }

    /*
     * Represents a small volume of the world.
     */
    class Chunk {
    public:
        static constexpr s32 width_bits = 5;
        static constexpr s32 height_bits = 5;
        static constexpr s32 length_bits = 5;

        // NOTE: Not sure if (width|height|length)_bits == 0 would work?
        static_assert(width_bits > 0);
        static_assert(height_bits > 0);
        static_assert(length_bits > 0);
        static_assert(width_bits + height_bits + length_bits <= 32);

        static constexpr s32 width  = 1 << width_bits;
        static constexpr s32 height = 1 << height_bits;
        static constexpr s32 length = 1 << length_bits;
        static constexpr s32 volume = width * length * height;

        static constexpr s32 width_mask = width - 1;
        static constexpr s32 height_mask = height - 1;
        static constexpr s32 length_mask = length - 1;

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

            Iterator(std::array<Block, volume> const* data, s32 pos) : m_data(data), m_position(pos) {}

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

            Iterator operator++(s32) { 
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
            s32 m_position;
        };

        Iterator begin() const { return Iterator(&m_data, 0); }
        Iterator end() const { return Iterator(&m_data, volume); }

    private:
        std::array<Block, volume> m_data;

        static s32 block_index(Position p) {
            auto index = p.y & height_mask;
            index |= (p.x & width_mask) << height_bits;
            index |= (p.z & length_mask) << (height_bits + width_bits);
            return index;
        }

        static Position block_position(s32 index) {
            s32 x = (index >> height_bits) & width_mask;
            s32 y = index & height_mask;
            s32 z = (index >> (height_bits + width_bits)) & length_mask;
            return {x, y, z};
        }
    };

    inline Position Position::block_to_chunk(Position position) {
        return { 
            position.x & Chunk::width_mask, 
            position.y & Chunk::height_mask,
            position.z & Chunk::length_mask
        };
    }

    class Terrain {
    public:
        Terrain(s32 width_chunks, s32 height_chunks, s32 length_chunks);

        s32 width_chunks() const { return m_width_chunks; }
        s32 height_chunks() const { return m_height_chunks; }
        s32 length_chunks() const { return m_length_chunks; }
        s32 volume_chunks() const { return width_chunks() * height_chunks() * length_chunks(); }

        s32 width_blocks() const { return width_chunks() * Chunk::width; }
        s32 height_blocks() const { return height_chunks() * Chunk::height; }
        s32 length_blocks() const { return length_chunks() * Chunk::length; }
        s32 volume_blocks() const { return width_blocks() * height_blocks() * length_blocks(); }

        Chunk *chunk(Position chunk_position);
        Chunk const* chunk(Position chunk_position) const;

        // TODO: Rename create_chunk to load_chunk and implement generation / loading logic.
        Chunk *create_chunk(Position chunk_position);
        // TODO: Rename delete_chunk to unload_chunk and implement unloading logic.
        void delete_chunk(Position chunk_position);

    private:
        std::unordered_map<s32, std::unique_ptr<Chunk>> m_chunks;
        s32 m_width_chunks, m_height_chunks, m_length_chunks;

        s32 chunk_index(Position cp) const {
            return cp.y + cp.x * height_chunks() + cp.z * width_chunks() * height_chunks();
        }
    };

    class LoadedArea {
    public:
        LoadedArea(Terrain &terrain, Position center_chunk, s32 radius_chunks);

        void update_loaded_volume(Position center_chunk) {
            update_loaded_volume(center_chunk, radius_chunks());
        }

        void update_loaded_volume(Position center_chunk, s32 radius_chunks);

        Terrain &terrain() { return m_terrain; }
        Terrain const& terrain() const { return m_terrain; }
        s32 radius_chunks() const { return m_radius_chunks; }
        s32 diameter_chunks() const { return 2 * m_radius_chunks; }
        Position center_chunk() const { return m_center_chunk; }

    private:
        Terrain &m_terrain;
        Position m_center_chunk;
        s32 m_radius_chunks;
        std::vector<Chunk*> m_chunks;

        s32 chunk_index(Position rcp) {
            Position center = center_chunk();
            Position cp = {
                rcp.x + center.x,
                rcp.y + center.y,
                rcp.z + center.z
            };
            return cp.y + cp.x * diameter_chunks() + cp.z * diameter_chunks() * diameter_chunks();
        }
    };

    /*
     * Processes chunks as they are created, loaded, generated, updated, unloaded and
     * destroyed. Any chunk can be in one of a number of states at any given time:
     *   - Created
     *     The chunk has just been created and contaisn no meaningful block data. The data
     *     must now be loaded or generated.
     *
     *   - Updated
     *     The chunk has just been modified and its mesh must be recomputed. (Possibly
     *     along with other data...)
     *
     *   - Loaded
     *     The chunk has been loaded or generated and contains actual terrain data. This
     *     is the resting state most chunks are going to be in.
     *
     *   - Unloaded
     *     The chunk contains actual data but is no longer loaded. Its data can be saved
     *     to disk at this point.
     *
     *   - Unused
     *     The chunk is not in use and may be freed or reused. While it may contain
     *     meaningful data, it's best to assume it contains garbage.
     *
     *  The ChunkProcessor contains a queue of chunk pointers. Chunks may be added to the
     *  queue as needed and will be processed one by one, moving them from one state to
     *  the next using whatever method is necessary.
     *
     *  The state transitions are as follows:
     *   - Created --> Updated
     *     The chunk is loaded from disk or generated. Its mesh must be generated for
     *     display and other data may be computed too.
     *
     *   - Loaded --> Loaded
     *     Currently chunks in the loaded state should not be submitted at all. So a
     *     Loaded chunk is simply skipped. (In practice, we check if a chunk is Loaded
     *     before even adding it to the queue to save effort.)
     *
     *     IDEA: In the future, we may implement this transition to simulate fluids or do
     *     other dynamic things. (Though a 'Loaded --> Updated' transition probably makes
     *     more sense...)
     *
     *   - Unloaded --> Unused
     *     The data of an unloaded chunk may be saved to disk before its state is updated.
     *     As this is currently not needed, we will simply change the state immediately
     *     instead of adding the chunk to the queue.
     *
     *  Any other state transitions are up to the user and must happen elsewhere. Reusing
     *  an Unused chunk will require the state to be manually set to Created. Same for
     *  freeing it. Changing the state from Loaded to Updated when a block is changed is
     *  also up to the user, meant to be done wherever the block placement logic is
     *  handled.
     *
     *  Internally the ChunkProcessor is intended to use a lockfree thread pool to
     *  accomplish the transitions since they can lock up the thread for a while.
     *  (Recomputing a mesh can be costly, disk IO operations can block for a while, ...)
     */
    class ChunkProcessor {

    };
}

#endif // SIVOX_GAME_VOXELTERRAIN_HPP
