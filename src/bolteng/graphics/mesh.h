#ifndef MESH_H
#define MESH_H

#include "../defines.h"
#include <glm/glm.hpp>
#include <filesystem>
#include <optional>
#include <vector>

namespace bolt {
    struct Vertex {
        glm::vec3 m_position;
        glm::vec3 m_normal;
        glm::vec2 m_texture;
    };

    struct Texture {
        uint32_t m_id;
        std::string m_type;
    };

    struct Mesh {
        std::vector<Vertex>   m_vertices;
        std::vector<uint32_t> m_indices;
        std::vector<Texture>  m_textures;

        Mesh();
        Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
        void draw();
        void setup();

    private:
        uint32_t vao, vbo, ebo;
    };

    [[nodiscard]] std::optional<Mesh> assimp_load(std::filesystem::path const &path);

    [[nodiscard]] status::Status load_obj(std::filesystem::path const &path, Mesh &mesh);
}
#endif // MESH_H
