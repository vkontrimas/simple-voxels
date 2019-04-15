#include "voxelterrain.hpp"

namespace sivox {
    Terrain::Terrain(int width_chunks, int height_chunks, int length_chunks) :
        m_width_chunks(width_chunks), m_height_chunks(height_chunks), m_length_chunks(length_chunks) {}

    Chunk *Terrain::chunk(Position chunk_position) { 
        auto it = m_chunks.find(chunk_index(chunk_position));
        if (it == m_chunks.end()) { return nullptr; }
        else { return it->second.get(); }
    }
    Chunk const* Terrain::chunk(Position chunk_position) const {
        auto it = m_chunks.find(chunk_index(chunk_position));
        if (it == m_chunks.end()) { return nullptr; }
        else { return it->second.get(); }
    }

    Chunk *Terrain::create_chunk(Position chunk_position) {
        if (Chunk *c = chunk(chunk_position)) { return c; }
        else {
            auto index = chunk_index(chunk_position);
            m_chunks[index] = std::make_unique<Chunk>();
            return m_chunks[index].get();
        }
    }

    void Terrain::delete_chunk(Position chunk_position) {
        auto it = m_chunks.find(chunk_index(chunk_position));
        if (it != m_chunks.end()) {
            m_chunks.erase(it);
        }
    }
}
