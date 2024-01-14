#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../core/component.h"
#include <glm/glm.hpp>

class TransformComponent : public Component {

public:
    static ComponentId const ID;

    glm::vec3 m_position;
    float m_rotation;
    float m_uniform_scale;
    
    TransformComponent();

    virtual bool init(void *p_description) override final;
};

#endif // TRANSFORM_COMPONENT_H
