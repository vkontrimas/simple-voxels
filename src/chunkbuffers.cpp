#include "chunkbuffers.hpp"
#include <cassert>

namespace {
    const GLsizeiptr s_worst_vertex_count = sivox::Chunk::volume * 24;  // 4 verts per face, 6 faces per cube, 4 * 6 = 24
    const GLsizeiptr s_worst_element_count = sivox::Chunk::volume * 36; // 6 indices per face, 6 faces per cube, 6^2 = 36

    void set_up_buffers(sivox::ChunkBuffers const& buffers) {
        const GLenum buffer_usage = GL_STATIC_DRAW; // TODO: See how using GL_DYNAMIC_DRAW affects performance!
        const GLuint vertex_position_loc = 0; // TODO: Look this up in the shader in the future?

        glBindVertexArray(buffers.vertex_array());

        glBindBuffer(GL_ARRAY_BUFFER, buffers.vertex_buffer());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.element_buffer());

        glBufferData(
            GL_ARRAY_BUFFER, 
            s_worst_vertex_count * sizeof(sivox::ChunkMesh::Vertex), 
            nullptr, 
            buffer_usage
        );

        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, 
            s_worst_element_count * sizeof(sivox::ChunkMesh::TriangleIndex), 
            nullptr, 
            buffer_usage
        );

        glEnableVertexAttribArray(vertex_position_loc);
        glVertexAttribPointer(vertex_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

namespace sivox {
    ChunkBuffers::ChunkBuffers() : m_element_count(0) {
        glGenBuffers(m_buffers.size(), m_buffers.data());
        glGenVertexArrays(1, &m_vao);
        set_up_buffers(*this);
    }

    ChunkBuffers::ChunkBuffers(ChunkMesh const& mesh) : m_element_count(0) {
        glGenBuffers(m_buffers.size(), m_buffers.data());
        glGenVertexArrays(1, &m_vao);
        set_up_buffers(*this);
        set_mesh(mesh);
    }

    ChunkBuffers::~ChunkBuffers() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(m_buffers.size(), m_buffers.data());
    }

    void ChunkBuffers::set_mesh(ChunkMesh const& mesh) {
        assert(mesh.vertices.size() <= s_worst_vertex_count);
        assert(mesh.triangles.size() <= s_worst_element_count);

        m_element_count = mesh.triangles.size() > s_worst_element_count ? s_worst_element_count : mesh.triangles.size();

        /*
         * TODO: We're making a full copy of the mesh data here. Perhaps, ChunkMesh should be generated with the
         * appropriate number of verts and tri indices? We could then switch to using std::array over std::vector in
         * ChunkMesh.
         */
        ChunkMesh mesh_copy = mesh;

        mesh_copy.vertices.resize(s_worst_vertex_count, { glm::vec3(0.0f, 0.0f, 0.0f) });
        mesh_copy.triangles.resize(s_worst_element_count, 0);

        glBindVertexArray(vertex_array());
        glBufferSubData(GL_ARRAY_BUFFER, 0, s_worst_vertex_count * sizeof(ChunkMesh::Vertex), mesh_copy.vertices.data());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, s_worst_element_count * sizeof(ChunkMesh::TriangleIndex), mesh_copy.triangles.data());
        glBindVertexArray(0);
    }
}
