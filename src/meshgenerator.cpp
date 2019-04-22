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

    void emit_block(sivox::ChunkMesh &mesh, sivox::Position position, BlockSides sides) {
    }
}

namespace sivox {
    ChunkMesh generate_mesh(Chunk const& chunk) {
        ChunkMesh mesh = {};
        mesh.vertices.reserve(ChunkMesh::max_vertex_count);
        mesh.triangles.reserve(ChunkMesh::max_triangle_index_count);
        for (auto block : chunk) {
            if (block.block != 0) {
                Position p = block.position;
                s32 bitmask = BLOCK_SIDES_NONE;
                if (chunk.block({p.x, p.y + 1, p.z}) == 0) { bitmask |= BLOCK_SIDES_TOP; }
                if (chunk.block({p.x, p.y - 1, p.z}) == 0) { bitmask |= BLOCK_SIDES_BOTTOM; }
                if (chunk.block({p.x + 1, p.y, p.z}) == 0) { bitmask |= BLOCK_SIDES_RIGHT; }
                if (chunk.block({p.x - 1, p.y, p.z}) == 0) { bitmask |= BLOCK_SIDES_LEFT; }
                if (chunk.block({p.x, p.y, p.z + 1}) == 0) { bitmask |= BLOCK_SIDES_BACK; }
                if (chunk.block({p.x, p.y, p.z - 1}) == 0) { bitmask |= BLOCK_SIDES_FRONT; }

                s32 added_vertices = 0;

                /*
                 * TODO: 
                 * Later we can jam all the separate arrays of vertices into a single huge lookup table with 2^6 = 64 entries.
                 * Then we can just look up by passing the [bitmask] directly as the index.
                 */
                if (bitmask & BLOCK_SIDES_TOP) {
                    s32 triangle_start_index = mesh.vertices.size(); 
                    std::copy(s_block_top.begin(), s_block_top.end(), std::back_inserter(mesh.vertices));
                    std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
                    added_vertices += 4;

                    for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                        *it += triangle_start_index;
                    }
                }
                if (bitmask & BLOCK_SIDES_BOTTOM) {
                    s32 triangle_start_index = mesh.vertices.size(); 
                    std::copy(s_block_bottom.begin(), s_block_bottom.end(), std::back_inserter(mesh.vertices));
                    std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
                    added_vertices += 4;

                    for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                        *it += triangle_start_index;
                    }
                }
                if (bitmask & BLOCK_SIDES_RIGHT) {
                    s32 triangle_start_index = mesh.vertices.size(); 
                    std::copy(s_block_right.begin(), s_block_right.end(), std::back_inserter(mesh.vertices));
                    std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
                    added_vertices += 4;

                    for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                        *it += triangle_start_index;
                    }
                }
                if (bitmask & BLOCK_SIDES_LEFT) {
                    s32 triangle_start_index = mesh.vertices.size(); 
                    std::copy(s_block_left.begin(), s_block_left.end(), std::back_inserter(mesh.vertices));
                    std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
                    added_vertices += 4;

                    for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                        *it += triangle_start_index;
                    }
                }
                if (bitmask & BLOCK_SIDES_FRONT) {
                    s32 triangle_start_index = mesh.vertices.size(); 
                    std::copy(s_block_front.begin(), s_block_front.end(), std::back_inserter(mesh.vertices));
                    std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
                    added_vertices += 4;

                    for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                        *it += triangle_start_index;
                    }
                }
                if (bitmask & BLOCK_SIDES_BACK) {
                    s32 triangle_start_index = mesh.vertices.size(); 
                    std::copy(s_block_back.begin(), s_block_back.end(), std::back_inserter(mesh.vertices));
                    std::copy(s_triangles.begin(), s_triangles.end(), std::back_inserter(mesh.triangles));
                    added_vertices += 4;

                    for (auto it = mesh.triangles.end() - s_triangles.size(); it != mesh.triangles.end(); ++it) {
                        *it += triangle_start_index;
                    }
                }

                for (auto it = mesh.vertices.end() - added_vertices; it != mesh.vertices.end(); ++it) {
                    it->position += glm::vec3(p.x, p.y, p.z);
                }

            }
        }
        return mesh;
    } 
}
