#ifndef BASE_COMPONENT_SYSTEM_H
#define BASE_COMPONENT_SYSTEM_H

#include "entity.h"

class EntityManager;

class BaseComponentSystem {
protected:
    EntityManager *m_pEntityManager;

public:
    explicit BaseComponentSystem(EntityManager *pEntityManager) : m_pEntityManager(pEntityManager) {}
    virtual ~BaseComponentSystem() = default;

    virtual void onEntityCreated(Entity const &entity) = 0;
    virtual void onEntityDestroyed(EntityId entity) = 0;
    virtual void update(double deltaTime) = 0;
};

#endif // BASE_COMPONENT_SYSTEM_H
