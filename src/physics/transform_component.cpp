#include "transform_component.h"

EntityId const TransformComponent::ID = 0x40e447ad;

TransformComponent::TransformComponent() : m_rotation(0), m_uniform_scale(1.0f) {
}

bool TransformComponent::init(void *p_description) {
    return true;
}
