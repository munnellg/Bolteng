#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"
#include <limits>

class Component {
    static constexpr uint64_t INVALID_POOL_INDEX = std::numeric_limits<uint64_t>::max();

    EntityId m_entityId;
    size_t m_poolIndex;

public:
    Component();
    virtual ~Component() = default;
    virtual bool init(void *pDescription) = 0; // TODO

    EntityId getEntityId() const;

    void setPoolIndex(uint64_t index);
    uint64_t getPoolIndex() const;
};

#endif // COMPONENT_H
