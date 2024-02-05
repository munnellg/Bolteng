#include "framerate_component.h"

FramerateComponent::FramerateComponent() : m_currDeltaIdx(0) {
}

FramerateComponent::~FramerateComponent() {
}

std::array<uint64_t, FramerateComponent::MAX_DELTAS> const& FramerateComponent::getDeltas() const {
    return m_deltas;
}

void FramerateComponent::pushDelta(uint64_t const delta) {
    m_deltas[m_currDeltaIdx++ % FramerateComponent::MAX_DELTAS] = delta;
}
