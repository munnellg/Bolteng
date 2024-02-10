#include "sokoban.h"
#include "bolteng/defines.h"
#include "scene/level_scene.h"
#include "scene/splash_scene.h"
#include "bolteng/subsystems/subsystems.h"
#include "bolteng/logging.h"

#include <cstdint>
#include <iostream>
#include <functional>
#include <entt/entt.hpp>

Sokoban::Sokoban() : 
    bolt::BoltApp("Sokoban")
{
    m_currentScene = std::make_shared<LevelScene>();
}

bool Sokoban::postInit() {
    // TODO(gary): Handy quit shortcut for now. Delete later.
    bolt::input::keyboard.bind(bolt::input::KEY_ESCAPE, std::bind(&Sokoban::quitMainLoop, this));
    m_currentScene->onEnter();
    return true;
}

bool Sokoban::preQuit() {
    m_currentScene->onExit();
    return true;
}

