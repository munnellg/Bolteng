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

using namespace bolt;
using namespace bolt::input;

LevelScene::LevelScene() : 
        m_registry(),
        m_player(UNBOUND_ENTITY),
        m_worldCamera(UNBOUND_ENTITY),
        m_playerCamera(UNBOUND_ENTITY),
        m_currentLevel(0),
        m_renderSystem(&m_registry),
        m_moveSystem(&m_registry),
        m_collisionSystem(&m_registry),
        m_framerateSystem(&m_registry)
{
    m_systems.push_back(&m_collisionSystem);
    m_systems.push_back(&m_moveSystem);
    m_systems.push_back(&m_framerateSystem);
    m_systems.push_back(&m_renderSystem);

    m_framerate = m_registry.create();
    m_registry.emplace<FramerateComponent>(m_framerate);
}

void LevelScene::onEnter() {
    bolt::input::game_pads[0].bindButton(bolt::input::BUTTON_LEFT_SHOULDER, std::bind(&LevelScene::prev_level, this));
    bolt::input::game_pads[0].bindButton(bolt::input::BUTTON_RIGHT_SHOULDER, std::bind(&LevelScene::next_level, this));
    bolt::input::game_pads[0].bindEvent(bolt::input::GAME_PAD_CONNECT_EVENT, std::bind(&LevelScene::player_joined, this));
    bolt::input::game_pads[0].bindEvent(bolt::input::GAME_PAD_DISCONNECT_EVENT, std::bind(&LevelScene::player_left, this));

    bolt::input::keyboard.bind(bolt::input::KEY_UP, std::bind(&LevelScene::next_level, this));
    bolt::input::keyboard.bind(bolt::input::KEY_DOWN, std::bind(&LevelScene::prev_level, this));

    load_level(m_currentLevel);
}

void LevelScene::update(uint64_t deltaTime) {
    for (auto system : m_systems) {
        system->update(deltaTime);
    }
}

void LevelScene::onExit() {
    clear_level();
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

    if (m_registry.valid(m_worldCamera)) { 
        m_registry.destroy(m_worldCamera); 
    }

    if (m_registry.valid(m_playerCamera)) {
        m_registry.destroy(m_playerCamera);
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

    m_worldCamera  = bolt::entities::create_camera(m_registry, centre_x, centre_y, width, height);
    m_playerCamera = bolt::entities::create_camera(m_registry, m_level.player_start_x, -m_level.player_start_y, 8.0f * subsystems::display::aspect, 8.0f);

    m_registry.emplace<ActiveComponent>(m_worldCamera);

    bolt::input::keyboard.bind(bolt::input::KEY_TAB, std::bind(&LevelScene::switchCamera, this));

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

    m_registry.sort<RenderComponent>([](const RenderComponent &lhs, const RenderComponent &rhs) {
        return lhs.m_layer < rhs.m_layer;
    });
}

int LevelScene::switchCamera() {

    auto cam_view = m_registry.view<CameraComponent, ActiveComponent>();
    auto camera = cam_view.front();

    if (!m_registry.valid(camera)) {
        return 1;
    }

    m_registry.remove<ActiveComponent>(camera);

    if (camera == m_playerCamera) {
        m_registry.emplace<ActiveComponent>(m_worldCamera);
    } else {
        m_registry.emplace<ActiveComponent>(m_playerCamera);
    }

    return 0;
}

int LevelScene::prev_level() {
    if (--m_currentLevel >= 60) {
        m_currentLevel = 59;
    }

    load_level(m_currentLevel);

    return 0;
}

int LevelScene::next_level() {
    if (++m_currentLevel >= 60) {
        m_currentLevel = 0;
    }

    load_level(m_currentLevel);

    return 0;
}

int LevelScene::player_joined() {
    LOG_INFO("Player joined");
    return 0;
}

int LevelScene::player_left() {
    LOG_INFO("Player left");
    return 0;
}
