#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "component.h"
#include "base_component_system.h"
#include "entity_system_types.h"

#include <map>
#include <vector>

class EntityManager {
    using Entities   = std::map<EntityId, Entity>;
    using Components = std::vector<std::vector<Component*>>;
    using Systems    = std::vector<BaseComponentSystem *>;

    Entities m_entities;
    Components m_components;
    Systems m_systems;

public:
    EntityManager();
    EntityManager(EntityManager const &) = delete;
    EntityManager& operator=(EntityManager const &) = delete;
    EntityManager(EntityManager const &&) = delete;
    EntityManager& operator=(EntityManager const &&) = delete;
    ~EntityManager();

    bool createSystems();
    void update(double delta_ms);

    EntityId createEntity();
    void destroyEntity();
};

#endif // ENTITY_MANAGER_H
