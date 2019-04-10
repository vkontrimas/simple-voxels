#include "chunkbuffers.hpp"
#include <cassert>

namespace {
    void set_up_buffers(sivox::ChunkBuffers const& buffers) {
        const GLenum buffer_usage = GL_STATIC_DRAW; // TODO: See how using GL_DYNAMIC_DRAW affects performance!
        const GLuint vertex_position_loc = 0; // TODO: Look this up in the shader in the future?
        const GLuint vertex_normal_loc = 1; // TODO: Look this up in the shader in the future?

        glBindVertexArray(buffers.vertex_array());

        glBindBuffer(GL_ARRAY_BUFFER, buffers.vertex_buffer());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.element_buffer());

        glBufferData(
            GL_ARRAY_BUFFER, 
            sivox::ChunkMesh::worst_vertex_count * sizeof(sivox::ChunkMesh::Vertex), 
            nullptr, 
            buffer_usage
        );

        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, 
            sivox::ChunkMesh::worst_triangle_index_count * sizeof(sivox::ChunkMesh::TriangleIndex), 
            nullptr, 
            buffer_usage
        );

        glEnableVertexAttribArray(vertex_position_loc);
        glEnableVertexAttribArray(vertex_normal_loc);

        glVertexAttribPointer(vertex_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
        glVertexAttribPointer(vertex_normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(sizeof(GLfloat) * 3));

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
        assert(mesh.vertices.size() <= ChunkMesh::worst_vertex_count);
        assert(mesh.triangles.size() <= ChunkMesh::worst_triangle_index_count);

        m_element_count = mesh.triangles.size() > ChunkMesh::worst_triangle_index_count ? ChunkMesh::worst_triangle_index_count : mesh.triangles.size();

        /*
         * TODO: We're making a full copy of the mesh data here. Perhaps, ChunkMesh should be generated with the
         * appropriate number of verts and tri indices? We could then switch to using std::array over std::vector in
         * ChunkMesh.
         */
        ChunkMesh mesh_copy = mesh;

        mesh_copy.vertices.resize(ChunkMesh::worst_vertex_count, { glm::vec3(0.0f, 0.0f, 0.0f) });
        mesh_copy.triangles.resize(ChunkMesh::worst_triangle_index_count, 0);

        glBindVertexArray(vertex_array());
        glBufferSubData(GL_ARRAY_BUFFER, 0, ChunkMesh::worst_vertex_count * sizeof(ChunkMesh::Vertex), mesh_copy.vertices.data());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, ChunkMesh::worst_triangle_index_count * sizeof(ChunkMesh::TriangleIndex), mesh_copy.triangles.data());
        glBindVertexArray(0);
    }
}
