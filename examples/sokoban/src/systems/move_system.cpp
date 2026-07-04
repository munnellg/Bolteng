#include "move_system.h"
#include "../components/move_component.h"
#include <bolteng/components/position_component.h>
#include <bolteng/logging.h>
#include <entt/entt.hpp>
#include <numeric>

MoveSystem::MoveSystem(entt::registry *pRegistry) : bolt::ComponentSystem(pRegistry) {
}

void MoveSystem::update(uint64_t) {

    auto view = m_pRegistry->view<MoveComponent, PositionComponent>();
    for (auto [entity, move, position]: view.each()) {
        glm::vec3 dist = glm::vec3(1.0f);
        position.m_position += move.m_direction * dist;
        m_pRegistry->remove<MoveComponent>(entity);
    }
}
