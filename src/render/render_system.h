#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "render_component.h"
#include "../core/component_system.h"

class RenderSystem : public ComponentSystem<RenderComponent> {
    using BaseType = ComponentSystem<RenderComponent>;

public:
    RenderSystem(EntityManager *pEntityManager);

    void update(double deltaTime) override;
    bool init() override;
};

#endif // RENDER_SYSTEM_H
