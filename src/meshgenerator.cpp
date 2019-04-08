#include "meshgenerator.hpp"
#include <algorithm>
#include <iterator>

namespace {
    const std::vector<sivox::ChunkMesh::Vertex> s_block_top {
        /*
         * Top face
         */
        { glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
        { glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
    };

    const std::vector<sivox::ChunkMesh::Vertex> s_block_bottom {
        /*
         * Bottom face
         */
        { glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, -1.0f, 0.0f) },
        { glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(0.0f, -1.0f, 0.0f) },
    };

    const std::vector<sivox::ChunkMesh::Vertex> s_block_right {
        /*
         * Right face
         */
        { glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f) },
    };

    const std::vector<sivox::ChunkMesh::Vertex> s_block_left {
        /*
         * Left face
         */
        { glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(-1.0f, 0.0f, 0.0f) },
        { glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(-1.0f, 0.0f, 0.0f) },
        { glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
        { glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
    };

    const std::vector<sivox::ChunkMesh::Vertex> s_block_front {
        /*
         * Front face
         */
        { glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
        { glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
        { glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
    };

    const std::vector<sivox::ChunkMesh::Vertex> s_block_back {
        /*
         * Back face
         */
        { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
        { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
        { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }
    };

    const std::vector<sivox::ChunkMesh::TriangleIndex> s_triangles {
        0, 1, 2, 2, 3, 0
    };
}

namespace sivox {
    void emit_block(ChunkMesh &mesh, Position position, BlockSides sides) {
        int added_vertices = 0;

        /*
         * TODO: 
         * Later we can jam all the separate arrays of vertices into a single huge lookup table with 2^6 = 64 entries.
         * Then we can just look up by passing the [sides] bitmask directly as the index.
         */
        if (sides & BLOCK_SIDES_TOP) {
            int triangle_start_index = mesh.vertices.size(); 
            std::copy(s_block_top.begin(), s_block_top.end(), std::back_inserter(mesh.vertices));
            std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
            added_vertices += 4;

            for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                *it += triangle_start_index;
            }
        }
        if (sides & BLOCK_SIDES_BOTTOM) {
            int triangle_start_index = mesh.vertices.size(); 
            std::copy(s_block_bottom.begin(), s_block_bottom.end(), std::back_inserter(mesh.vertices));
            std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
            added_vertices += 4;

            for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                *it += triangle_start_index;
            }
        }
        if (sides & BLOCK_SIDES_RIGHT) {
            int triangle_start_index = mesh.vertices.size(); 
            std::copy(s_block_right.begin(), s_block_right.end(), std::back_inserter(mesh.vertices));
            std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
            added_vertices += 4;

            for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                *it += triangle_start_index;
            }
        }
        if (sides & BLOCK_SIDES_LEFT) {
            int triangle_start_index = mesh.vertices.size(); 
            std::copy(s_block_left.begin(), s_block_left.end(), std::back_inserter(mesh.vertices));
            std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
            added_vertices += 4;

            for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                *it += triangle_start_index;
            }
        }
        if (sides & BLOCK_SIDES_FRONT) {
            int triangle_start_index = mesh.vertices.size(); 
            std::copy(s_block_front.begin(), s_block_front.end(), std::back_inserter(mesh.vertices));
            std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
            added_vertices += 4;

            for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                *it += triangle_start_index;
            }
        }
        if (sides & BLOCK_SIDES_BACK) {
            int triangle_start_index = mesh.vertices.size(); 
            std::copy(s_block_back.begin(), s_block_back.end(), std::back_inserter(mesh.vertices));
            std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
            added_vertices += 4;

            for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                *it += triangle_start_index;
            }
        }

        for (auto it = mesh.vertices.end() - added_vertices; it != mesh.vertices.end(); ++it) {
            it->position += glm::vec3(position.x, position.y, position.z);
        }
    }
}
