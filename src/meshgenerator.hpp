#pragma once
#ifndef SIVOX_GAME_MESHGENERATOR_HPP
#define SIVOX_GAME_MESHGENERATOR_HPP

#include "common.hpp"
#include <glm/glm.hpp>
#include <vector>
#include "voxelterrain.hpp"

namespace sivox {
    /*
     * Represents a single chunk's mesh.
     * Contains a vector of vertices and a vector of triangle indices.
     */
    struct ChunkMesh {
        static constexpr s32 max_vertex_count = Chunk::volume * 24; // 4 verts per face * 6 faces = 24 verts
        static constexpr s32 max_triangle_count = Chunk::volume * 12; // 2 triangles per face * 6 faces = 12
        static constexpr s32 max_triangle_index_count = max_triangle_count * 3; // 3 indices per triangle

        using TriangleIndex = u32;
        struct Vertex {
            glm::vec3 position;
            glm::vec3 normal;
        };

        std::vector<Vertex> vertices;
        std::vector<TriangleIndex> triangles;
    };

    /*
     * Generates a mesh for a single [chunk].
     */
    ChunkMesh generate_mesh(Chunk const& chunk);
};

#endif // SIVOX_GAME_MESHGENERATOR_HPP
