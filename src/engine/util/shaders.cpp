#include "shaders.h"
#include <fstream>
#include <GL/glew.h>
#include <vector>

int
load_file(std::filesystem::path const &path, std::string &buffer) {
    std::ifstream in(path);

    if (!in.is_open()) {
        return 0;
    }

    buffer.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    in.close();

    return 1;
}

int
compile_shader(GLuint &id, std::filesystem::path const &path, GLenum const shader_type) {
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
        delete[] log;
        return 0;
    }

    return 1;
}

void
load_shader(std::filesystem::path const &src_file) {
}
