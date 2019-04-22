#pragma once
#ifndef SIVOX_GAME_SHADER_HPP
#define SIVOX_GAME_SHADER_HPP

#include "common.hpp"
#include <string>
#include <glad/glad.h>

namespace sivox {
    class Shader {
    public:
        Shader() : m_program(0) {}
        explicit Shader(std::string const& vertex_src, std::string const& fragment_src); 

        ~Shader();

        Shader(Shader const& other) = delete;
        Shader &operator=(Shader const& other) = delete;

        Shader(Shader &&other) : m_program(other.m_program) {
            other.m_program = 0;
        }
        Shader &operator=(Shader &&other) {
            m_program = other.m_program;
            other.m_program = 0;
			return *this;
        }

        GLuint program() const { return m_program; }
        operator GLuint() const { return program(); }

        static Shader load(std::string const& name);

    private:
        GLuint m_program;
    };
}
#endif // SIVOX_GAME_SHADER_HPP
