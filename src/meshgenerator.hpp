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
     * Adds block vertices to the [mesh] at the given [position].
     */
    void emit_block(ChunkMesh &mesh, Position position);

    /*
     * Generates a mesh for a single [chunk].
     */
    template<int WIDTH, int HEIGHT>
    inline ChunkMesh generate_mesh(ChunkTemplate<WIDTH, HEIGHT> const& chunk) {
        ChunkMesh mesh = {};
        for (auto block : chunk) {
            if (block.block != 0) {
                emit_block(mesh, block.position);
            }
        }
        return mesh;
    }
};

#endif // SIVOX_GAME_MESHGENERATOR_HPP
