#ifndef SCENE_LEVEL
#define SCENE_LEVEL

#include "../engine/core/engine.h"
#include "../model/level.h"

#include <cstdint>
#include <vector>

class LevelScene {
public:

    LevelScene();
    void update(uint64_t delta);
    void load_level(size_t level_id);

private:
    void clear_level();

    entt::registry m_registry;
    entt::entity m_actor;

    Level m_level;
    std::vector<entt::entity> m_walls;
    std::vector<entt::entity> m_background;
    std::vector<entt::entity> m_crates;
    std::vector<entt::entity> m_targets;
    entt::entity m_player;
    entt::entity m_camera;
    entt::entity m_framerate;

    std::vector<ComponentSystem *> m_systems;
    FramerateSystem m_framerateSystem;
    RenderSystem m_renderSystem;
};

#endif // SCENE_LEVEL
