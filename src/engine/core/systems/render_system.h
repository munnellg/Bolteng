#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "component_system.h"

class RenderSystem : public ComponentSystem {

public:
    RenderSystem(entt::registry *m_pRegistry);

    void update(uint64_t deltaTime) override;
};

#endif // RENDER_SYSTEM_H
