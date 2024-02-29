#include "shader.h"
#include "../logging.h"

#include <algorithm>
#include <GL/glew.h>
#include <string>
#include <filesystem>
#include <fstream>

inline int load_file(std::filesystem::path const &path, std::string &buffer) {
    std::ifstream in(path.generic_string());

    if (!in.is_open()) {
        LOG_ERROR("file not found '%s'", path.generic_string().c_str());
        return 0;
    }

    buffer.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    in.close();

    return 1;
}

inline int compile_shader(GLuint &id, std::filesystem::path const &path, GLenum const shader_type) {
    GLint status;
    std::string src;

    if (!load_file(path, src)) {
        return 0;
    }

    char const * const srcstr = src.c_str();
    id = glCreateShader(shader_type);
    glShaderSource(id, 1, &srcstr, NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        GLint lsize;
        GLchar *log = new GLchar[lsize];
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lsize);
        glGetShaderInfoLog(id, lsize, nullptr, log);
        LOG_ERROR("%s", log);
        delete[] log;
        return 0;
    }

    return 1;
}

inline GLenum gl_shader_type(bolt::ShaderType const &type) {
    switch (type) {
        case bolt::ShaderType::VERTEX:
            return GL_VERTEX_SHADER;
        case bolt::ShaderType::FRAGMENT:
            return GL_FRAGMENT_SHADER;
        default:
            return GL_INVALID_ENUM;
    }
}

namespace bolt {
    Shader::Shader() :
        m_shaderId(0)
    {}

    Shader::Shader(std::filesystem::path file, ShaderType type) :
        m_shaderId(0),
        m_type(type),
        m_file(file)
    {}

    ShaderProgram::ShaderProgram() : 
        m_programId(0)
    {}

    ShaderProgram::ShaderProgram(uint32_t programId) : 
        m_programId(programId)
    {}

    uint32_t ShaderProgram::getUniform(std::string const &uniform) {
        return glGetUniformLocation(m_programId, uniform.c_str());
    }

    void ShaderProgram::enable() {
        glUseProgram(m_programId);
    }

    void ShaderProgram::disable() {
        glUseProgram(0);
    }

    std::optional<ShaderProgram> ShaderProgram::build(std::filesystem::path const &vshader, std::filesystem::path const &fshader) {
        std::vector<Shader> shaders = {
            { vshader, ShaderType::VERTEX },
            { fshader, ShaderType::FRAGMENT }
        };
        return ShaderProgram::build(shaders);
    }

    std::optional<ShaderProgram> ShaderProgram::build(std::vector<Shader> &shaders) {
        ShaderProgram shader_program(static_cast<uint32_t>(glCreateProgram()));

        for (Shader shader : shaders) {
            compile_shader(shader.m_shaderId, shader.m_file, gl_shader_type(shader.m_type));
            glAttachShader(shader_program.m_programId, shader.m_shaderId);
        }

        glLinkProgram(shader_program.m_programId);

        std::for_each(shaders.begin(), shaders.end(), [&] (auto &shader) {
            glDetachShader(shader_program.m_programId, shader.m_shaderId);
            glDeleteShader(shader.m_shaderId);
        });

        return std::make_optional(std::move(shader_program));
    }
}
