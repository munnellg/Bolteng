#include "render_system.h"
#include "GL/glew.h"
#include "../subsystems/subsystems.h"

RenderSystem::RenderSystem(entt::registry *pRegistry) : ComponentSystem(pRegistry) {
}

void RenderSystem::update(uint64_t deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    subsystems::display::swap();
}
