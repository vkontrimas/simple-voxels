#include <voxelterrain.hpp>
#include <ostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace sivox;

static std::ostream &operator<<(std::ostream &stream, Block block) {
    stream << "[Block "
           << block.id
           << "]";
    return stream;
}

static std::ostream &operator<<(std::ostream &stream, Position p) {
    stream << "[Position "
           << p.x
           << ", "
           << p.y
           << ", "
           << p.z
           << "]";
    return stream;
}

static std::ostream &operator<<(std::ostream &stream, Chunk::Iterator::Value val) {
    stream << "[Value "
           << val.position
           << " "
           << val.block
           << "]";
    return stream;
}

static bool operator==(Chunk::Iterator::Value a, Chunk::Iterator::Value b) {
    return a.position == b.position && a.block == b.block;
}

static bool operator!=(Chunk::Iterator::Value a, Chunk::Iterator::Value b) {
    return !(a == b);
}

static void chunk_for_each(std::function<void(Position)> func) {
    for (int x = 0; x < Chunk::width; ++x) {
        for (int z = 0; z < Chunk::width; ++z) {
            for (int y = 0; y < Chunk::height; ++y) {
                func({x, y, z});
            }
        }
    }
}
#include <catch2/catch.hpp>

TEST_CASE("Block : Initialize", "[terrain][blocks]") {
    for (int i = 0; i < Block::max_id; ++i) {
        Block block1 = i;
        REQUIRE(block1.id == i);

        Block block2(i);
        REQUIRE(block2.id == i);
    }
}

TEST_CASE("Chunk : Initialize", "[terrain][blocks][chunks]") {
    Chunk chunk;
    chunk_for_each([&chunk](Position pos) {
        REQUIRE(chunk.block(pos) == 0);
    });
}

TEST_CASE("Chunk : Iterator (all blocks)", "[terrain][blocks][chunks]") {
    using Catch::Equals;
    Chunk chunk;

    std::vector<Chunk::Iterator::Value> expected;
    for (int z = 0; z < Chunk::width; ++z) {
        for (int x = 0; x < Chunk::width; ++x) {
            for (int y = 0; y < Chunk::height; ++y) {
                expected.push_back({ { x, y, z }, 0 });
            }
        }
    }

    std::vector<Chunk::Iterator::Value> result;
    for (auto value : chunk) {
        result.push_back(value);
    }

    REQUIRE(expected.size() == result.size());
    for (int i = 0; i < expected.size(); ++i) {
        REQUIRE(expected[i] == result[i]);
    }
}

TEST_CASE("Chunk : Fill", "[terrain][blocks][chunks]") {
    Chunk chunk;

    int counter = 0;
    chunk_for_each([&chunk, &counter](Position pos) {
        chunk.set_block(pos, counter);
        ++counter;
        if (counter > Block::max_id) { counter = 0; }
    });

    counter = 0;
    chunk_for_each([&chunk, &counter](Position pos) {
        REQUIRE(chunk.block(pos) == counter);
        ++counter;
        if (counter > Block::max_id) { counter = 0; }
    });
}

TEST_CASE("Chunk : Out of bounds access (top and bottom)", "[terrain][blocks][chunks]") {
    Chunk chunk;

    for (int x = -1; x < Chunk::width + 1; ++x) {
        for (int z = -1; z < Chunk::width + 1; ++z) {
            Position top = {x, Chunk::height + 1, z};
            Position bottom = {x, -1, z};

            INFO("top " << top << " bottom " << bottom);

            REQUIRE(chunk.block(top) == 0);
            REQUIRE(chunk.block(bottom) == 0);

            chunk.set_block(top, 1);
            chunk.set_block(bottom, 1);

            REQUIRE(chunk.block(top) == 0);
            REQUIRE(chunk.block(bottom) == 0);
        }
    }
}

TEST_CASE("Chunk : Out of bounds access (sides)", "[terrain][blocks][chunks]") {
    Chunk chunk;

    for (int i = -1; i <= Chunk::width + 1; ++i) {
        for (int y = -1; y <= Chunk::height + 1; ++y) {
            Position x_pos = { Chunk::width, y, i };
            Position x_neg = { -1, y, i };
            Position z_pos = { i, y, Chunk::width };
            Position z_neg = { i, y, -1 };

            INFO("x_pos " << x_pos << " x_neg " << x_neg << " z_pos " << z_pos << " z_neg " << z_neg);

            REQUIRE(chunk.block(x_pos) == 0);
            REQUIRE(chunk.block(x_neg) == 0);
            REQUIRE(chunk.block(z_pos) == 0);
            REQUIRE(chunk.block(z_neg) == 0);

            chunk.set_block(x_pos, 1);
            chunk.set_block(x_neg, 1);
            chunk.set_block(z_pos, 1);
            chunk.set_block(z_neg, 1);

            REQUIRE(chunk.block(x_pos) == 0);
            REQUIRE(chunk.block(x_neg) == 0);
            REQUIRE(chunk.block(z_pos) == 0);
            REQUIRE(chunk.block(z_neg) == 0);
        }
    }
}

TEST_CASE("Terrain : size", "[terrain]") {
    struct Value {
        int w, h, l;

        int volume() const { return w * h * l; }
    };
    std::vector<Value> values = {
        {1, 2, 3},
        {2, 2, 2},
        {32, 32, 32},
        {64, 64, 64},
        {10, 20, 30},
        {30, 20, 10},
        {512, 32, 512}
    };

    for (auto val : values) {
        Terrain terrain(val.w, val.h, val.l);
        REQUIRE(terrain.width_chunks() == val.w);
        REQUIRE(terrain.height_chunks() == val.h);
        REQUIRE(terrain.length_chunks() == val.l);
        REQUIRE(terrain.volume_chunks() == val.volume());
        REQUIRE(terrain.width_blocks() == val.w * Chunk::width);
        REQUIRE(terrain.height_blocks() == val.h * Chunk::height);
        REQUIRE(terrain.length_blocks() == val.l * Chunk::length);
        REQUIRE(terrain.volume_blocks() == val.volume() * Chunk::volume);
    }
}

TEST_CASE("Terrain : empty after initialization", "[terrain][chunks]") {
    Terrain terrain(32, 32, 32);
    Terrain const& const_terrain = terrain;

    for (int z = 0; z < terrain.length_chunks(); ++z) {
        for (int x = 0; x < terrain.width_chunks(); ++x) {
            for (int y = 0; y < terrain.height_chunks(); ++y) {
                REQUIRE(terrain.chunk({x, y, z}) == nullptr);
                REQUIRE(const_terrain.chunk({x, y, z}) == nullptr);
            }
        }
    }
}

TEST_CASE("Terrain : chunk lifecycle", "[terrain][chunks]") {
    Terrain terrain(1, 1, 1);
    Terrain const& const_terrain = terrain;
    Position position = {0, 0, 0};

    REQUIRE(terrain.chunk(position) == nullptr);
    REQUIRE(const_terrain.chunk(position) == nullptr);

    Chunk *created_chunk = terrain.create_chunk(position);
    REQUIRE(created_chunk != nullptr);
    REQUIRE(terrain.chunk(position) == created_chunk);
    REQUIRE(const_terrain.chunk(position) == created_chunk);

    terrain.delete_chunk(position);
    REQUIRE(terrain.chunk(position) == nullptr);
    REQUIRE(const_terrain.chunk(position) == nullptr);
}

TEST_CASE("Terrain : chunk lifecycle (several positions)", "[terrain][chunks]") {
    Terrain terrain(32, 32, 32);
    Terrain const& const_terrain = terrain;
    std::vector<Position> positions = {
        {0, 0, 0},
        {1, 1, 1},
        {20, 30, 10},
        {5, 6, 9},
        {17, 20, 0},
        {15, 4, 19},
    };

    /*
     * Create chunks at given positions.
     */
    std::vector<Chunk*> created_chunks;
    for (Position position : positions) {
        Chunk *chunk = terrain.create_chunk(position);
        REQUIRE(chunk != nullptr);
        created_chunks.push_back(chunk);
    }

    /*
     * Try retrieving every chunk.
     * Chunks we created should exist now.
     * Others should not.
     */
    for (int z = 0; z < terrain.length_chunks(); ++z) {
        for (int x = 0; x < terrain.width_chunks(); ++x) {
            for (int y = 0; y < terrain.height_chunks(); ++y) {
                if (std::find(positions.begin(), positions.end(), Position{x, y, z}) == positions.end()) {
                    REQUIRE(terrain.chunk({x, y, z}) == nullptr);
                    REQUIRE(const_terrain.chunk({x, y, z}) == nullptr);
                }
                else {
                    REQUIRE_FALSE(terrain.chunk({x, y, z}) == nullptr);
                    REQUIRE_FALSE(const_terrain.chunk({x, y, z}) == nullptr);
                }
            }
        }
    }

    /*
     * Validate newly created chunk pointers.
     */
    REQUIRE(positions.size() == created_chunks.size());
    for (int i = 0; i < positions.size(); ++i) {
        REQUIRE(terrain.chunk(positions[i]) == created_chunks[i]);
        REQUIRE(const_terrain.chunk(positions[i]) == created_chunks[i]);
    }

    /*
     * Delete chunks.
     */
    for (Position position : positions) {
        terrain.delete_chunk(position);
    }
    created_chunks.clear();

    /*
     * None of the chunks should exist anymore!
     */
    for (int z = 0; z < terrain.length_chunks(); ++z) {
        for (int x = 0; x < terrain.width_chunks(); ++x) {
            for (int y = 0; y < terrain.height_chunks(); ++y) {
                REQUIRE(terrain.chunk({x, y, z}) == nullptr);
                REQUIRE(const_terrain.chunk({x, y, z}) == nullptr);
            }
        }
    }
}
