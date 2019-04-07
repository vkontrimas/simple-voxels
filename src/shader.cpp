#include "shader.hpp"
#include "ioutils.hpp"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>

namespace fs = std::filesystem;

namespace {
    constexpr int ERROR_MESSAGE_LENGTH = 1024;

    enum class ShaderType {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER
    };

    GLuint create_shader(std::string const& source_code, ShaderType type) {
        GLuint shader = glCreateShader(static_cast<GLenum>(type));
        if (shader) {
            /*
             * glShaderSource expects an array of C strings so we need to do this weird assignment to get the address of
             * the string.
             */
            char const* source_code_c_str = source_code.c_str();

            glShaderSource(shader, 1, &source_code_c_str, nullptr);
            glCompileShader(shader);

            GLint compiled;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLchar message[ERROR_MESSAGE_LENGTH];
                glGetShaderInfoLog(shader, ERROR_MESSAGE_LENGTH, nullptr, message);

                std::ofstream err("err.txt");
                err << "create_shader : OpenGL error: \n" << message << std::endl;
            }
        }
        return shader;
    }

    template<class SHADER_IT> 
    GLuint create_program(SHADER_IT begin, SHADER_IT end) {
        GLuint program = glCreateProgram();
        if (program) {
            for (auto it = begin; it != end; ++it) {
                glAttachShader(program, *it);
            }
            glLinkProgram(program);

            GLint linked;
            glGetProgramiv(program, GL_LINK_STATUS, &linked);

            if (!linked) {
                GLchar message[ERROR_MESSAGE_LENGTH];
                glGetProgramInfoLog(program, ERROR_MESSAGE_LENGTH, nullptr, message);

                std::ofstream err("err.txt");
                err << "create_program : OpenGL error: \n" << message << std::endl;
            }

            for (auto it = begin; it != end; ++it) {
                glDetachShader(program, *it);
            }
        }
        return program;
    }
}

namespace sivox {
    Shader::Shader(std::string const& vertex_src, std::string const& fragment_src) {
        std::array<GLuint, 2> shaders {
            create_shader(vertex_src, ShaderType::Vertex),
            create_shader(fragment_src, ShaderType::Fragment),
        };

        m_program = create_program(shaders.begin(), shaders.end());

        for (GLuint shader : shaders) {
            glDeleteShader(shader);
        }
    }

    Shader::~Shader() {
        if (m_program) {
            glDeleteProgram(m_program);
            m_program = 0;
        }
    }

    Shader Shader::load(std::string const& name) {
        const fs::path shader_dir = "shaders";

        fs::path vertex_path = shader_dir / name;
        vertex_path += ".vert";

        fs::path fragment_path = shader_dir / name;
        fragment_path += ".frag";

        return Shader(read_text_file(vertex_path), read_text_file(fragment_path));
    }
}
