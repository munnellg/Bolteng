#ifndef MESH_H
#define MESH_H

#include "../defines.h"

#include <filesystem>

namespace bolt {
    namespace graphics {

        struct Mesh {
        };

        [[nodiscard]] status::Status load_obj(std::filesystem::path const &path, Mesh &mesh);
    }
}
#endif // MESH_H
