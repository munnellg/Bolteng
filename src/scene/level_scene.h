#ifndef SCENE_LEVEL
#define SCENE_LEVEL

#include "../engine/core/components/framerate_component.h"
#include "../engine/core/systems/framerate_system.h"
#include "../engine/core/systems/render_system.h"

#include <cstdint>
#include <entt/entt.hpp>
#include <vector>

class LevelScene {
public:

    LevelScene();
    void update(uint64_t delta);
private:
    entt::registry m_registry;

    std::vector<ComponentSystem *> m_systems;
    FramerateSystem m_framerateSystem;
    RenderSystem m_renderSystem;
};

#endif // SCENE_LEVEL
