#include "render_model.h"
#include "scene/render_3d_scene.h"
#include <bolteng/defines.h>
#include <bolteng/input/input.h>
#include <bolteng/subsystems/subsystems.h>
#include <bolteng/logging.h>

#include <cstdint>
#include <iostream>
#include <functional>
#include <entt/entt.hpp>

RenderModel::RenderModel() : 
    bolt::BoltApp("RenderModel")
{
    m_currentScene = std::make_shared<Render3DScene>();
}

bool RenderModel::postInit() {
    // TODO(gary): Handy quit shortcut for now. Delete later.
    bolt::input::keyboard.bind(bolt::input::KEY_ESCAPE, std::bind(&RenderModel::quitMainLoop, this));
    m_currentScene->onEnter();
    return true;
}

bool RenderModel::preQuit() {
    m_currentScene->onExit();
    return true;
}

