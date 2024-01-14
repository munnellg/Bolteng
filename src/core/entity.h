#ifndef ENTITY_H
#define ENTITY_H

#include "entity_system_types.h"
#include <map>

class Component;

class Entity {
    using ComponentMap = std::map<ComponentId, Component *>;

    EntityId m_id;
    ComponentMap m_components;

public:
    explicit Entity(EntityId id);

    EntityId getId() const;

    template <class CompType>
    void addComponent(CompType *pComp);

    template <class CompType>
    CompType *getComponent() const;

    ComponentMap const & getComponents() const;
};

#endif // ENTITY_H
