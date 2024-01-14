#include "entity.h"
#include "component.h"

Entity::Entity(EntityId id) : m_id(id) {}

EntityId Entity::getId() const {
    return m_id;
}

template <class CompType>
void Entity::addComponent(CompType *pComp) {
    if (m_components.find(CompType::ID) == m_components.end()) {
        m_components.emplace(CompType::ID, pComp);
    }
}

template <class CompType>
CompType *Entity::getComponent() const {
    auto findIt = m_components.find(CompType::ID);

    if (findIt != m_components.end()) {
        return findIt->second;
    }

    return nullptr;
}

Entity::ComponentMap const& Entity::getComponents() const {
    return m_components;
}
