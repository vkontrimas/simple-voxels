#include "voxelterrain.hpp"

namespace sivox {
    Terrain::Terrain(s32 width_chunks, s32 height_chunks, s32 length_chunks) :
        m_width_chunks(width_chunks), m_height_chunks(height_chunks), m_length_chunks(length_chunks) {}

    Chunk *Terrain::chunk(Position chunk_position) { 
        if (chunk_position.x < 0 || chunk_position.x >= width_chunks()) { return nullptr; }
        if (chunk_position.y < 0 || chunk_position.y >= height_chunks()) { return nullptr; }
        if (chunk_position.z < 0 || chunk_position.z >= length_chunks()) { return nullptr; }

        auto it = m_chunks.find(chunk_index(chunk_position));
        if (it == m_chunks.end()) { return nullptr; }
        else { return it->second.get(); }
    }
    Chunk const* Terrain::chunk(Position chunk_position) const {
        if (chunk_position.x < 0 || chunk_position.x >= width_chunks()) { return nullptr; }
        if (chunk_position.y < 0 || chunk_position.y >= height_chunks()) { return nullptr; }
        if (chunk_position.z < 0 || chunk_position.z >= length_chunks()) { return nullptr; }

        auto it = m_chunks.find(chunk_index(chunk_position));
        if (it == m_chunks.end()) { return nullptr; }
        else { return it->second.get(); }
    }

    Chunk *Terrain::create_chunk(Position chunk_position) {
        if (chunk_position.x < 0 || chunk_position.x >= width_chunks()) { return nullptr; }
        if (chunk_position.y < 0 || chunk_position.y >= height_chunks()) { return nullptr; }
        if (chunk_position.z < 0 || chunk_position.z >= length_chunks()) { return nullptr; }

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

    LoadedArea::LoadedArea(Terrain &terrain, Position center_chunk, s32 radius_chunks) : m_terrain(terrain) {
        update_loaded_volume(center_chunk, radius_chunks);
    }

    void LoadedArea::update_loaded_volume(Position new_center_chunk, s32 new_radius_chunks) {
        m_center_chunk = new_center_chunk;
        m_radius_chunks = new_radius_chunks;
        
        s32 radius = radius_chunks();
        s32 diameter = diameter_chunks();

        m_chunks.resize(diameter * diameter * diameter, nullptr);

        for (s32 z = 0; z < diameter; ++z) {
            for (s32 x = 0; x < diameter; ++x) {
                for (s32 y = 0; y < diameter; ++y) {
                    Position position = {x, y, z};
                    f32 distance = Position::distance(position, center_chunk());
                    if (distance <= radius) {
                        Chunk *chunk = terrain().chunk(position);
                        if (!chunk) {
                            chunk = terrain().create_chunk(position);
                        }
                        // TODO: Increase chunk ref count
                        m_chunks[chunk_index(position)] = chunk;
                    }
                    else {
                        // TODO: If already loaded, decrease chunk ref count
                        terrain().delete_chunk(position);
                        m_chunks[chunk_index(position)] = nullptr;
                    }
                }
            }
        }
    }
}
