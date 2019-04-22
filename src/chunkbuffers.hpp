#pragma once
#ifndef SIVOX_GAME_CHUNKBUFFERS_HPP
#define SIVOX_GAME_CHUNKBUFFERS_HPP

#include "common.hpp"
#include <array>
#include <glad/glad.h>
#include "meshgenerator.hpp"

namespace sivox {
    class ChunkBuffers {
    public:
        ChunkBuffers();
        explicit ChunkBuffers(ChunkMesh const& mesh);

        ~ChunkBuffers();

        ChunkBuffers(ChunkBuffers const& other) = delete;
        ChunkBuffers &operator=(ChunkBuffers const& other) = delete;

        ChunkBuffers(ChunkBuffers &&other) {
            m_vao = other.m_vao;
            m_buffers[0] = other.m_buffers[0];
            m_buffers[1] = other.m_buffers[1];

            other.m_vao = 0;
            other.m_buffers[0] = 0;
            other.m_buffers[1] = 0;
        }

        ChunkBuffers &operator=(ChunkBuffers &&other) {
            m_vao = other.m_vao;
            m_buffers[0] = other.m_buffers[0];
            m_buffers[1] = other.m_buffers[1];

            other.m_vao = 0;
            other.m_buffers[0] = 0;
            other.m_buffers[1] = 0;

            return *this;
        }

        void set_mesh(ChunkMesh const& mesh);

        GLuint vertex_array() const { return m_vao; }
        GLuint vertex_buffer() const { return m_buffers[0]; }
        GLuint element_buffer() const { return m_buffers[1]; } 
        s32 element_count() const { return m_element_count; }

    private:
        GLuint m_vao;
        std::array<GLuint, 2> m_buffers;
        s32 m_element_count;
    };
}
#endif // SIVOX_GAME_CHUNKBUFFERS_HPP
