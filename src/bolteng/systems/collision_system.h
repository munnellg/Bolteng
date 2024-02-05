#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "component_system.h"

class CollisionSystem : public ComponentSystem {

public:
    CollisionSystem(entt::registry *m_pRegistry);

    void update(uint64_t deltaTime) override;
};

#endif // COLLISION_SYSTEM_H
