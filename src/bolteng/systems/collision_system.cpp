#include "collision_system.h"
#include "../components/components.h"
#include "../logging.h"
#include <entt/entt.hpp>
#include <numeric>

CollisionSystem::CollisionSystem(entt::registry *pRegistry) : ComponentSystem(pRegistry) {
}

void CollisionSystem::update(uint64_t deltaTime) {

    auto movingCollidable = m_pRegistry->view<MoveComponent, PositionComponent, CollisionComponent>();

    for (auto [mEntity, mMove, mPosition, mCollision]: movingCollidable.each()) {
        checkForCollisions(mEntity, mMove, mPosition, mCollision);
    }
}

bool CollisionSystem::tryPush(entt::entity mEntity, MoveComponent &direction, PositionComponent &mPosition, CollisionComponent &mCollision) {
    if (!m_pRegistry->try_get<PushableComponent>(mEntity)) {
        return false;
    }

    // optimistically assume it can move
    MoveComponent mMove;
    mMove.m_direction = direction.m_direction;
    mMove.m_speed = direction.m_speed;
    m_pRegistry->emplace<MoveComponent>(mEntity, mMove);
    bool collisions = checkForCollisions(mEntity, mMove, mPosition, mCollision);

    return !collisions;
}

bool CollisionSystem::checkForCollisions(entt::entity mEntity, MoveComponent &mMove, PositionComponent &mPosition, CollisionComponent &mCollision) {
    // glm::vec3 newPos = mPosition.m_position + mMove.m_direction * glm::vec3((mMove.m_speed * deltaTime) / 1000.0f);
    glm::vec3 newPos = mPosition.m_position + mMove.m_direction;

    auto allCollidable = m_pRegistry->view<PositionComponent, CollisionComponent>();
    for (auto [cEntity, cPosition, cCollision]: allCollidable.each()) {
        
        // don't compare an entity to itself
        if (cEntity == mEntity) {
            continue;
        }

        if (collides(newPos, mCollision, cPosition, cCollision)) {
            
            // see if we can move the thing we hit
            if (m_pRegistry->try_get<PusherComponent>(mEntity)) {
                if (!tryPush(cEntity, mMove, cPosition, cCollision)) {
                    // if not then we stop moving
                    m_pRegistry->remove<MoveComponent>(mEntity);
                    return true;
                }
            } else {
                m_pRegistry->remove<MoveComponent>(mEntity);
                return true;
            }
        }
    }

    return false;
}

bool CollisionSystem::collides(glm::vec3 const &pos1, CollisionComponent const &col1, PositionComponent const &pos2, CollisionComponent const &col2) {
    return (pos1.x < pos2.m_position.x + col2.w &&
            pos1.x + col1.w > pos2.m_position.x &&
            pos1.y < pos2.m_position.y + col2.h &&
            pos1.y + col1.h > pos2.m_position.y);
}
