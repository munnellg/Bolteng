#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "../components/collision_component.h"
#include "../components/move_component.h"

#include <bolteng/systems/component_system.h>
#include <bolteng/components/components.h>
#include <glm/glm.hpp>

class CollisionSystem : public bolt::ComponentSystem {

public:
    CollisionSystem(entt::registry *m_pRegistry);

    void update(uint64_t deltaTime) override;

private:

    bool tryPush(entt::entity mEntity, MoveComponent &direction, PositionComponent &mPosition, CollisionComponent &mCollision);
    bool checkForCollisions(entt::entity mEntity, MoveComponent &mMove, PositionComponent &mPosition, CollisionComponent &mCollision);
    bool collides(glm::vec3 const &pos1, CollisionComponent const &col1, PositionComponent const &pos2, CollisionComponent const &col2);
};

#endif // COLLISION_SYSTEM_H
