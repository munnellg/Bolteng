#ifndef ENTITY_COMPONENT_SYSTEM_H
#define ENTITY_COMPONENT_SYSTEM_H

#include <cstdint>
#include <entt/entt.hpp>

class ComponentSystem {

public:
    ComponentSystem(entt::registry *pRegistry) : m_pRegistry(pRegistry) {}
    virtual ~ComponentSystem() = default;

    virtual void update(uint64_t deltaTime) = 0;

protected:
    entt::registry *m_pRegistry;
};

#endif // ENTITY_COMPONENT_SYSTEM_H
