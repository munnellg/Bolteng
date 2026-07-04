#ifndef MOVE_SYSTEM_H
#define MOVE_SYSTEM_H

#include <bolteng/systems/component_system.h>

class MoveSystem : public bolt::ComponentSystem {

public:
    MoveSystem(entt::registry *m_pRegistry);

    void update(uint64_t deltaTime) override;
};
#endif // MOVE_SYSTEM_H
