#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

namespace bolt {
    enum ShaderType { VERTEX, FRAGMENT };

    struct Shader {
        uint32_t m_shaderId;
        ShaderType m_type;
        std::filesystem::path m_file;

        Shader();
        Shader(std::filesystem::path file, ShaderType type);
    };

    struct ShaderProgram {
        ShaderProgram();
        ShaderProgram(uint32_t programId);

        uint32_t getUniform(std::string const &uniform);
        void enable();
        void disable();

        static std::optional<ShaderProgram> build(std::filesystem::path const &vshader, std::filesystem::path const &fshader);
        static std::optional<ShaderProgram> build(std::vector<Shader> &shaders);

    private:
        uint32_t m_programId;
    };
}
#endif // SHADER_H
