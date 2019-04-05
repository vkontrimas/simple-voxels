#include "meshgenerator.hpp"

namespace {
    const std::vector<sivox::ChunkMesh::Vertex> s_block_vertices {
        /*
         * Top face
         */
        { glm::vec3(0.0f, 1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f) },
        { glm::vec3(0.0f, 1.0f, -1.0f) },

        /*
         * Bottom face
         */
        { glm::vec3(0.0f, 0.0f, 0.0f) },
        { glm::vec3(0.0f, 0.0f, -1.0f) },
        { glm::vec3(1.0f, 0.0f, -1.0f) },
        { glm::vec3(1.0f, 0.0f, 0.0f) },

        /*
         * Right face
         */
        { glm::vec3(1.0f, 0.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, -1.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f) },

        /*
         * Left face
         */
        { glm::vec3(0.0f, 0.0f, 0.0f) },
        { glm::vec3(0.0f, 1.0f, 0.0f) },
        { glm::vec3(0.0f, 1.0f, -1.0f) },
        { glm::vec3(0.0f, 0.0f, -1.0f) },

        /*
         * Front face
         */
        { glm::vec3(0.0f, 0.0f, -1.0f) },
        { glm::vec3(0.0f, 1.0f, -1.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f) },
        { glm::vec3(1.0f, 0.0f, -1.0f) },

        /*
         * Back face
         */
        { glm::vec3(0.0f, 0.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f) },
        { glm::vec3(0.0f, 1.0f, 0.0f) }
    };

    const std::vector<sivox::ChunkMesh::TriangleIndex> s_block_triangles {
        0, 1, 2, 2, 3, 0,       // Top face
        4, 5, 6, 6, 7, 4,       // Bottom face
        8, 9, 10, 10, 11, 8,    // Right face
        12, 13, 14, 14, 15, 12, // Left face
        16, 17, 18, 18, 19, 16, // Front face
        20, 21, 22, 22, 23, 20  // Back face
    };
}

namespace sivox {
    void emit_block(ChunkMesh &mesh, Position position) {
        int triangle_start_index = mesh.vertices.size(); 
        for (auto const& vertex : s_block_vertices) {
            mesh.vertices.push_back({
                vertex.position + glm::vec3(position.x, position.y, position.z)
            });
        }

        for (auto triangle : s_block_triangles) {
            mesh.triangles.push_back(triangle + triangle_start_index);
        }
    }
}
