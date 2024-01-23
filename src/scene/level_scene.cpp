#include "level_scene.h"

LevelScene::LevelScene()  : 
        m_registry(),
        m_framerateSystem(&m_registry),
        m_renderSystem(&m_registry)
{
    m_systems.push_back(&m_framerateSystem);
    m_systems.push_back(&m_renderSystem);

    entt::entity const entity = m_registry.create();
    m_registry.emplace<FramerateComponent>(entity);
}

void LevelScene::update(uint64_t delta) {
    for (auto system : m_systems) {
        system->update(delta);
    }
}


