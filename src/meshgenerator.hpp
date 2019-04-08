#pragma once
#ifndef SIVOX_GAME_MESHGENERATOR_HPP
#define SIVOX_GAME_MESHGENERATOR_HPP

#include <glm/glm.hpp>
#include <vector>
#include "voxelterrain.hpp"

namespace sivox {
    /*
     * Represents a single chunk's mesh.
     * Contains a vector of vertices and a vector of triangle indices.
     */
    struct ChunkMesh {
        using TriangleIndex = unsigned int;
        struct Vertex {
            glm::vec3 position;
            glm::vec3 normal;
        };

        std::vector<Vertex> vertices;
        std::vector<TriangleIndex> triangles;
    };

    /*
     * Classic enum because enum class doesn't support bitwise ops. EWWW
     */
    enum BlockSides {
        BLOCK_SIDES_NONE   = 0x000,

        BLOCK_SIDES_TOP    = 0x001,
        BLOCK_SIDES_BOTTOM = 0x002,
        BLOCK_SIDES_LEFT   = 0x004,
        BLOCK_SIDES_RIGHT  = 0x008,
        BLOCK_SIDES_FRONT  = 0x010,
        BLOCK_SIDES_BACK   = 0x020,

        BLOCK_SIDES_ALL    = 0x03F
    };

    /*
     * Adds block vertices to the [mesh] at the given [position].
     * The bitmask [sides] indicates which sides of the block should be added.
     */
    void emit_block(ChunkMesh &mesh, Position position, BlockSides sides);

    /*
     * Generates a mesh for a single [chunk].
     */
    template<int WIDTH, int HEIGHT>
    inline ChunkMesh generate_mesh(ChunkTemplate<WIDTH, HEIGHT> const& chunk) {
        ChunkMesh mesh = {};
        for (auto block : chunk) {
            if (block.block != 0) {
                Position p = block.position;
                int bitmask = BLOCK_SIDES_NONE;
                if (chunk.block({p.x, p.y + 1, p.z}) == 0) { bitmask |= BLOCK_SIDES_TOP; }
                if (chunk.block({p.x, p.y - 1, p.z}) == 0) { bitmask |= BLOCK_SIDES_BOTTOM; }
                if (chunk.block({p.x + 1, p.y, p.z}) == 0) { bitmask |= BLOCK_SIDES_RIGHT; }
                if (chunk.block({p.x - 1, p.y, p.z}) == 0) { bitmask |= BLOCK_SIDES_LEFT; }
                if (chunk.block({p.x, p.y, p.z + 1}) == 0) { bitmask |= BLOCK_SIDES_BACK; }
                if (chunk.block({p.x, p.y, p.z - 1}) == 0) { bitmask |= BLOCK_SIDES_FRONT; }

                emit_block(mesh, block.position, static_cast<BlockSides>(bitmask));
            }
        }
        return mesh;
    }
};

#endif // SIVOX_GAME_MESHGENERATOR_HPP
