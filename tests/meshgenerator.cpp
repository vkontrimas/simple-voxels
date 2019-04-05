#include <meshgenerator.hpp>
#include <catch2/catch.hpp>

using namespace sivox;

static bool operator==(ChunkMesh::Vertex a, ChunkMesh::Vertex b) {
    return a.position == b.position;
}
static bool operator!=(ChunkMesh::Vertex a, ChunkMesh::Vertex b) {
    return !(a == b);
}

/*
 * Define a smaller 4 x 4 x 4 chunk so we can reasonably
 * test the mesh generation against actual meshes.
 * Hand typing a 32 x 32 x 32 mesh would take a rather long time.
 */
using TestChunk = ChunkTemplate<4, 4>;

/*
 * We'll just test empty chunks and individual blocks.
 * If we test a whole chunk with random data we'll pretty much be reimplementing the mesh generator here.
 *
 * TODO: Maybe in the future we can test occluded faces not being generated or greedy meshing related stuff.
 */
TEST_CASE("MeshGenerator : Empty chunk", "[terrain][blocks][chunks][meshes]") {
    INFO("Chunk dimensions: " << TestChunk::width << "x" << TestChunk::height << "x" << TestChunk::width);

    TestChunk chunk;
    for (auto block : chunk) {
        REQUIRE(block.block == 0);
    }

    ChunkMesh mesh = generate_mesh(chunk);
    REQUIRE(mesh.vertices.size() == 0);
    REQUIRE(mesh.triangles.size() == 0);
}

TEST_CASE("MeshGenerator : emit_block @ every position", "[terrain][blocks][chunks][meshes]") {
    using Catch::Equals;

    INFO("Chunk dimensions: " << TestChunk::width << "x" << TestChunk::height << "x" << TestChunk::width);

    for (int z = 0; z < TestChunk::width; ++z) {
        for (int x = 0; x < TestChunk::width; ++x) {
            for (int y = 0; y < TestChunk::height; ++y) {
                ChunkMesh mesh = {};
                emit_block(mesh, {x, y, z});

                REQUIRE(mesh.vertices.size() == 24);
                std::vector<ChunkMesh::Vertex> expected_vertices {
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

                for (auto &vertex : expected_vertices) {
                    vertex.position += glm::vec3(x, y, z);
                }
                REQUIRE_THAT( mesh.vertices, Equals(expected_vertices));

                REQUIRE(mesh.triangles.size() == 36);
                REQUIRE_THAT(
                    mesh.triangles,
                    Equals(
                        std::vector<ChunkMesh::TriangleIndex> {
                            0, 1, 2, 2, 3, 0,       // Top face
                            4, 5, 6, 6, 7, 4,       // Bottom face
                            8, 9, 10, 10, 11, 8,    // Right face
                            12, 13, 14, 14, 15, 12, // Left face
                            16, 17, 18, 18, 19, 16, // Front face
                            20, 21, 22, 22, 23, 20  // Back face
                        }
                    )
                );
            }
        }
    }
}
