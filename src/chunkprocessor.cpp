#include "chunkprocessor.hpp"

namespace sivox {
    void ChunkProcessor::update() {
        while (Chunk *chunk = m_chunk_queue.front()) {
            m_chunk_queue.pop();
            if (!chunk) { continue; }

            if (chunk->state() == Chunk::Updated) {

            }
            else if (chunk->state() == Chunk::Created) {
                for (s32 z = 0; z < Chunk::length; ++z) {
                    for (s32 x = 0; x < Chunk::width; ++x) {
                        for (s32 y = 0; y < Chunk::length; ++y) {

                        }
                    }
                }
            }
            else if (chunk->state() == Chunk::Unloaded) {
                chunk->state() = Chunk::Unused;
            }
        }
    }
}
