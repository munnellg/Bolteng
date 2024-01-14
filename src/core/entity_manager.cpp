#include "entity_manager.h"
#include "logging.h"
#include "../render/render_system.h"

EntityManager::EntityManager() {
    // TODO: Temp -> create some test things
}

EntityManager::~EntityManager() {

}

bool EntityManager::createSystems() {
    LOG_INFO("Creating entity component systems");

    RenderSystem *renderSystem = new RenderSystem(this);
    renderSystem->init();

    m_systems.emplace_back(renderSystem);

    LOG_INFO("Entity component systems created");

    return true;
}

void EntityManager::update(double deltaMs) {
    for (auto& system : m_systems) {
        system->update(deltaMs);
    }
}

EntityId EntityManager::createEntity() {
    return 0;
}

void EntityManager::destroyEntity() {
}
