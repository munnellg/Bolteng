#ifndef SCENE_LEVEL
#define SCENE_LEVEL

#include "../bolteng/application/scene.h"
#include "../bolteng/bolteng.h"
#include "../model/level.h"
#include "../model/controller.h"

#include <cstdint>
#include <vector>

class LevelScene : public Scene {
public:

    LevelScene();
    void load_level(size_t level_id);
    int switchCamera();

    void onEnter() override;
    void update(uint64_t deltaTime) override;
    void onExit() override;

    int next_level();
    int prev_level();
    int player_joined();
    int player_left();

private:
    void clear_level();

    void spawnCrate(float x, float y);
    void spawnTarget(float x, float y);
    void spawnPlayer(float x, float y);
    void spawnWall(float x, float y);
    entt::entity spawnCamera(float x, float y, float w, float h);

    entt::registry m_registry;

    Level m_level;
    std::vector<entt::entity> m_walls;
    std::vector<entt::entity> m_background;
    std::vector<entt::entity> m_crates;
    std::vector<entt::entity> m_targets;

    entt::entity m_player;
    entt::entity m_worldCamera;
    entt::entity m_playerCamera;
    entt::entity m_framerate;

    size_t m_currentLevel; 

    std::vector<bolt::ComponentSystem *> m_systems;

    Controller m_playerController;

    bolt::RenderSystem m_renderSystem;
    bolt::MoveSystem m_moveSystem;
    bolt::CollisionSystem m_collisionSystem;
    bolt::FramerateSystem m_framerateSystem;
};

#endif // SCENE_LEVEL
