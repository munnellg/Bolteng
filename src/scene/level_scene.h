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
private:
    entt::registry m_registry;
    entt::entity m_actor;
    Level m_current_level;

    std::vector<ComponentSystem *> m_systems;
    FramerateSystem m_framerateSystem;
    RenderSystem m_renderSystem;
};

#endif // SCENE_LEVEL
