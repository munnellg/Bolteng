#include "level_scene.h"
#include "../engine/core/engine.h"
#include "../engine/core/logging.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

LevelScene::LevelScene()  : 
        m_registry(),
        m_framerateSystem(&m_registry),
        m_renderSystem(&m_registry)
{
    m_systems.push_back(&m_framerateSystem);
    m_systems.push_back(&m_renderSystem);

    entt::entity const entity = m_registry.create();
    m_registry.emplace<FramerateComponent>(entity);

    m_current_level = level_load(0);
    
    // render player
    engine::entities::create_actor(m_registry, m_current_level.player_start_x, -m_current_level.player_start_y, 1.0f, 65);
    
    // render everything else
    for (int y = 0; y < m_current_level.height; y++) {
        for (int x = 0; x < m_current_level.width; x++) {
            switch (m_current_level.tile_at(x, y)) {
                case MASK_WALL:
                    engine::entities::create_actor(m_registry, x, -y, 5.0f, 87);
                    break;
                case MASK_BOX:
                    engine::entities::create_actor(m_registry, x, -y, 3.0f, 1);
                    break;
                case MASK_TARGET:
                    engine::entities::create_actor(m_registry, x, -y, 4.0f, 39);
                    break;
                case BOX_ON_TARGET:
                    engine::entities::create_actor(m_registry, x, -y, 4.0f, 39);
                    engine::entities::create_actor(m_registry, x, -y, 3.0f, 1);
                    break;
                default:
                    break;
            }
        }
    }

    // generate static grass background
    for (float y = 1.0f; y >= -11.0f; y -= 1.0f) {
        for (float x = -0.0f; x <= 22.0f; x += 1.0f) {
            engine::entities::create_actor(m_registry, x, y, 0.0f, 88);
        }
    }

    subsystems::render::camera = engine::entities::create_camera(m_registry);
}

void LevelScene::update(uint64_t delta) {
    for (auto system : m_systems) {
        system->update(delta);
    }
}


