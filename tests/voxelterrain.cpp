#include <voxelterrain.hpp>
#include <ostream>
#include <functional>

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
        result.push_back(*value);
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
