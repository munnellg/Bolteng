#include "collision_system.h"
#include "../components/move_component.h"
#include "../components/position_component.h"
#include "../components/collision_component.h"
#include "../logging.h"
#include <entt/entt.hpp>
#include <numeric>

bool collides(glm::vec3 const &pos1, CollisionComponent const &col1, PositionComponent const &pos2, CollisionComponent const &col2) {
    return (pos1.x < pos2.m_position.x + col2.w &&
        pos1.x + col1.w > pos2.m_position.x &&
        pos1.y < pos2.m_position.y + col2.h &&
        pos1.y + col1.h > pos2.m_position.y);
}

CollisionSystem::CollisionSystem(entt::registry *pRegistry) : ComponentSystem(pRegistry) {
}

void CollisionSystem::update(uint64_t deltaTime) {

    auto movingCollidable = m_pRegistry->view<MoveComponent, PositionComponent, CollisionComponent>();
    auto allCollidable    = m_pRegistry->view<PositionComponent, CollisionComponent>();

    for (auto [mEntity, mMove, mPosition, mCollision]: movingCollidable.each()) {
        glm::vec3 newPos = mPosition.m_position + mMove.m_direction;

        for (auto [cEntity, cPosition, cCollision]: allCollidable.each()) {
            // don't compare an entity to itself
            if (cEntity == mEntity) {
                continue;
            }

            if (collides(newPos, mCollision, cPosition, cCollision)) {
                mMove.m_direction[0] = 0.0;
                mMove.m_direction[1] = 0.0;
                mMove.m_direction[2] = 0.0;
            }
        }
    }
}
