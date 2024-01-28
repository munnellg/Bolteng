#ifndef ACTOR_H
#define ACTOR_H

#include <entt/entt.hpp>

namespace engine {
    namespace entities {
        entt::entity create_actor(entt::registry &registry, float x, float y, float z, int tex_id);
        entt::entity create_camera(entt::registry &registry, float x, float y, float w, float h);
    }
}

#endif // ACTOR_H
