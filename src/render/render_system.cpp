#include "render_system.h"
#include "GL/glew.h"
#include "../core/subsystems/subsystems.h"

RenderSystem::RenderSystem(EntityManager *pEntityManager) : RenderSystem::BaseType(pEntityManager) {
}

void 
RenderSystem::update(double deltaTime) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto & compTuple : m_components) {
        RenderComponent * pRenderable = std::get<RenderComponent*>(compTuple);
    }

    subsystems::display::swap();
}

bool RenderSystem::init() {
    return true;
}
