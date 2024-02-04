#include "move_system.h"
#include "../components/move_component.h"
#include "../components/position_component.h"
#include "../logging.h"
#include <entt/entt.hpp>
#include <numeric>

MoveSystem::MoveSystem(entt::registry *pRegistry) : ComponentSystem(pRegistry) {
}

void MoveSystem::update(uint64_t deltaTime) {

    auto view = m_pRegistry->view<MoveComponent, PositionComponent>();
    for (auto [entity, move, position]: view.each()) {
        glm::vec3 dist = glm::vec3(1.0f);
        // glm::vec3 dist = glm::vec3((move.m_speed * deltaTime) / 1000.0f);
        position.m_position += move.m_direction * dist;
        move.m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
    }
}