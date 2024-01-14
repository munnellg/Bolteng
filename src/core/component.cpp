#include "component.h"

Component::Component() : 
    m_entityId(INVALID_ENTITY_ID), 
    m_poolIndex(INVALID_POOL_INDEX) {}

EntityId Component::getEntityId() const {
    return m_entityId;  
}

void Component::setPoolIndex(uint64_t index) {
    m_poolIndex = index;
}

uint64_t Component::getPoolIndex() const {
    return m_poolIndex;
}

