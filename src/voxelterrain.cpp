#include "voxelterrain.hpp"

namespace sivox {
    Terrain::Terrain(int width_chunks, int height_chunks, int length_chunks) :
        m_width_chunks(width_chunks), m_height_chunks(height_chunks), m_length_chunks(length_chunks) {}

    Chunk *Terrain::chunk(Position chunk_position) { return nullptr; }
    Chunk const* Terrain::chunk(Position chunk_position) const { return nullptr; }

    Chunk *Terrain::create_chunk(Position chunk_position) { return nullptr; }
    void Terrain::delete_chunk(Position chunk_position) {}
}
