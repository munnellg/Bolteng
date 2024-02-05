#include "level_scene.h"
#include "../bolteng/bolteng.h"
#include "../bolteng/logging.h"
#include "../bolteng/components/active_component.h"
#include "../bolteng/components/move_component.h"
#include "../bolteng/input/input.h"

#include <algorithm>
#include <GL/glew.h>
#include <glm/glm.hpp>

int const PLAYER_TEXTURE     = 1;
int const WALL_TEXTURE       = 25;
int const BACKGROUND_TEXTURE = 24;
int const CRATE_TEXTURE      = 13;
int const TARGET_TEXTURE     = 26;

using namespace bolt::input;

LevelScene::LevelScene() : 
        m_registry(),
        m_moveSystem(&m_registry),
        m_framerateSystem(&m_registry),
        m_collisionSystem(&m_registry),
        m_renderSystem(&m_registry),
        m_player(UNBOUND_ENTITY), // random uninitialized name entity id
        m_camera(UNBOUND_ENTITY)
{
    m_systems.push_back(&m_collisionSystem);
    m_systems.push_back(&m_moveSystem);
    m_systems.push_back(&m_framerateSystem);
    m_systems.push_back(&m_renderSystem);

    m_framerate = m_registry.create();
    m_registry.emplace<FramerateComponent>(m_framerate);
}

void LevelScene::clear_level() {
    auto destroy = [&](entt::entity const &e) { m_registry.destroy(e); };

    std::for_each(m_walls.begin(), m_walls.end(), destroy);
    m_walls.clear();

    std::for_each(m_crates.begin(), m_crates.end(), destroy);
    m_crates.clear();

    std::for_each(m_targets.begin(), m_targets.end(), destroy);
    m_targets.clear();

    std::for_each(m_background.begin(), m_background.end(), destroy);
    m_background.clear();

    if (m_registry.valid(m_player)) { 
        m_registry.destroy(m_player); 
    }

    if (m_registry.valid(m_camera)) { 
        m_registry.destroy(m_camera); 
    }
}

void LevelScene::spawnPlayer(float x, float y) {
    // render player
    m_player = bolt::entities::create_actor(m_registry, x, y, 1.0f, PLAYER_TEXTURE);
    
    // player can bump into things
    m_registry.emplace<CollisionComponent>(m_player);

    // player can push things that are pushable
    m_registry.emplace<PusherComponent>(m_player);
}

void LevelScene::spawnWall(float x, float y) {
    auto wall = bolt::entities::create_actor(m_registry, x, y, 5.0f, WALL_TEXTURE);

    // walls can bump into things
    m_registry.emplace<CollisionComponent>(wall);

    m_walls.emplace_back(wall);
}

void LevelScene::spawnCrate(float x, float y) {
    auto crate = bolt::entities::create_actor(m_registry, x, y, 3.0f, CRATE_TEXTURE);

    // crates can bump into things
    m_registry.emplace<CollisionComponent>(crate);

    // crates are pushable by a pusher
    m_registry.emplace<PushableComponent>(crate);

    m_crates.emplace_back(crate);
}


void LevelScene::spawnTarget(float x, float y) {
    auto target = bolt::entities::create_actor(m_registry, x, y, 4.0f, TARGET_TEXTURE);
    m_targets.emplace_back(target);
}

void LevelScene::load_level(size_t level_id) {

    clear_level();

    m_level = level_load(level_id);

    spawnPlayer(m_level.player_start_x, -m_level.player_start_y);
    
    // render everything else
    for (int y = 0; y < m_level.height; y++) {
        for (int x = 0; x < m_level.width; x++) {
            switch (m_level.tile_at(x, y)) {
                case MASK_WALL:
                    spawnWall(x, -y);
                    break;
                case MASK_BOX:
                    spawnCrate(x, -y);
                    break;
                case MASK_TARGET:
                    spawnTarget(x, -y);
                    break;
                case BOX_ON_TARGET:
                    spawnTarget(x, -y);
                    spawnCrate(x, -y);
                    break;
                default:
                    break;
            }
        }
    }
    
    // figure out the screen area for camera
    float width = (float) ((level_id == 0) ? 23 : m_level.width) + 2.0f;
    float height = (float) m_level.height + 2.0f;

    if (m_level.width < height * subsystems::display::aspect) {
        width = height * subsystems::display::aspect;
    } else {
        height = width / subsystems::display::aspect;
    }
    
    float centre_x = ((float) m_level.width - 1) / 2.0f;
    float centre_y = -((float) m_level.height - 1) / 2.0f;

    float y_min = std::ceil(centre_y + height / 2.0f);
    float y_max = std::floor(centre_y - height / 2.0f);
    float x_min = std::floor(centre_x - width / 2.0f);
    float x_max = std::ceil(centre_x + width / 2.0f);

    m_camera = bolt::entities::create_camera(m_registry, centre_x, centre_y, width, height);
    m_registry.emplace<ActiveComponent>(m_camera);

    // generate static grass background to fill the camera area
    for (float y = y_min; y >= y_max; y -= 1.0f) {
        for (float x = x_min; x <= x_max; x += 1.0f) {
            m_background.emplace_back(bolt::entities::create_actor(m_registry, x, y, 0.0f, BACKGROUND_TEXTURE));
        }
    }

    // bind movement controls to the player
    m_playerController.bind(m_player, &m_registry);
    m_playerController.bind(keyboard);
    m_playerController.bind(game_pads[0]);
}

void LevelScene::update(uint64_t delta) {
    for (auto system : m_systems) {
        system->update(delta);
    }
}


