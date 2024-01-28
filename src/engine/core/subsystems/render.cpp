#include "subsystems.h"
#include "../logging.h"

#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <vector>

namespace subsystems {
    namespace render {
        entt::entity camera;
        uint32_t shader_program;

        GLuint tex;
        std::filesystem::path const vertex_shader_file = "assets/shaders/vshader.glsl";
        std::filesystem::path const fragment_shader_file = "assets/shaders/fshader.glsl";
        std::filesystem::path const textures_file = "assets/textures/pokemon.png";

        int load_file(std::filesystem::path const &path, std::string &buffer) {
            std::ifstream in(path.generic_string());

            if (!in.is_open()) {
                LOG_ERROR("file not found '%s'", path.generic_string().c_str());
                return 0;
            }

            buffer.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

            in.close();

            return 1;
        }

        int compile_shader(GLuint &id, std::filesystem::path const &path, GLenum const shader_type) {
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

        int build_shader_program() {
            GLuint vshader, fshader;


            if (!compile_shader(vshader, vertex_shader_file, GL_VERTEX_SHADER)) {
                return 0;
            }

            if (!compile_shader(fshader, fragment_shader_file, GL_FRAGMENT_SHADER)) {
                glDeleteShader(vshader);
                return 0;
            }

            shader_program = glCreateProgram();
            glAttachShader(shader_program, vshader);
            glAttachShader(shader_program, fshader);
            glLinkProgram(shader_program);
            glDetachShader(shader_program, vshader);
            glDetachShader(shader_program, fshader);
            glDeleteShader(vshader);
            glDeleteShader(fshader);

            glUseProgram(shader_program);

            return 1;
        }

        int load_textures() {
            SDL_Surface *surface = IMG_Load(textures_file.c_str());
            if (!surface) {
                LOG_ERROR("IMG_Load error: %s", IMG_GetError());
                return 0;
            }

            // Generate OpenGL texture
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
            SDL_FreeSurface(surface);

            // Set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            return 1;
        }

        int init() {
            LOG_INFO("Initializing render subsystem");

            if (!build_shader_program()) {
                return 0;
            }

            if (!load_textures()) {
                return 0;
            }

            return 1;
        }

        void quit() {
        } 
    }
}

        


