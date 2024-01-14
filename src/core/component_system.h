#ifndef ENTITY_COMPONENT_SYSTEM_H
#define ENTITY_COMPONENT_SYSTEM_H

#include "entity.h"
#include "base_component_system.h"
#include <vector>

template <class... Comps>
class ComponentSystem : public BaseComponentSystem {
    using EntityIdToIndexMap = std::map<EntityId, size_t>;
    EntityIdToIndexMap m_entityIdToIndexMap;

protected:
    using CompTuple = std::tuple<std::add_pointer_t<Comps>...>; // tuple of component pointers
    std::vector<CompTuple> m_components;

public:
    ComponentSystem(EntityManager *pEntityManager) : BaseComponentSystem(pEntityManager) {}
    virtual ~ComponentSystem() = default;
    virtual bool init() = 0;

    virtual void onEntityCreated(Entity const &entity) override final;
    virtual void onEntityDestroyed(EntityId entityId) override final;

private:
    // recursively looks through component types
    template <size_t INDEX, class CompType, class... CompArgs>
    bool processEntityComponent(ComponentId compId, Component *pComponent, CompTuple &tupleToFill);
     
    // This is the termination specification of the recursion, which happens 
    // when we no longer have a CompType that's passed in
    template <size_t INDEX>
    bool processEntityComponent(ComponentId compId, Component *pComponent, CompTuple &tupleToFill);
};

template <class... Comps>
void ComponentSystem<Comps...>::onEntityCreated(Entity const &entity) {
    // loop through all the components on this entity and see if any tuples match
    CompTuple compTuple;
    size_t matchingComps = 0;

    for (auto &compPair : entity.getComponents()) {
        if (processEntityComponent<0, Comps...>(compPair.first, compPair.second, compTuple)) {
            matchingComps++;
            if (matchingComps == sizeof...(Comps)) {
                m_components.emplace_back(std::move(compTuple));
                m_entityIdToIndexMap.emplace(entity.getId(), m_components.size() - 1);
                break;
            }
        }
    }
}

template <class... Comps>
void ComponentSystem<Comps...>::onEntityDestroyed(EntityId entityId) {
    auto const findIt = m_entityIdToIndexMap.find(entityId);
    if (findIt != m_entityIdToIndexMap.end()) {
        // move the back element to overwrite this one
        m_components[findIt->second] = std::move(m_components.back());
        m_components.pop_back();

        // we need to figure out which entity the moved component belongs to so
        // we can update the id to indx map. Since all components in a single
        // tuple are owned by the same entity, we can just grab the first one
        // and query its id
        auto const * pMovedComp = std::get<0>(m_components[findIt->second]);

        // find the entry for the moved id and update it with the new index
        auto movedTupleIt = m_entityIdToIndexMap.find(pMovedComp->getEntityId());
        movedTupleIt->second = findIt->second;
    }
}

template <class... Comps>
template <size_t INDEX, class CompType, class... CompArgs>
bool ComponentSystem<Comps...>::processEntityComponent(ComponentId compId, Component *pComponent, CompTuple &tupleToFill) {
    if (CompType::ID == compId) {
        std::get<INDEX>(tupleToFill) = static_cast<CompType*>(pComponent);
        return true;
    }

    return processEntityComponent<INDEX + 1, CompArgs...>(compId, pComponent, tupleToFill);
}

template <class... Comps>
template <size_t INDEX>
bool ComponentSystem<Comps...>::processEntityComponent(ComponentId compId, Component *pComponent, CompTuple &tupleToFill) {
    return false;
}

#endif // ENTITY_COMPONENT_SYSTEM_H
