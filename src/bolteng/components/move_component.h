#ifndef MOVE_COMPONENT
#define MOVE_COMPONENT

#include <glm/glm.hpp>
#include "../logging.h"

struct MoveComponent {
    glm::vec3 m_direction = glm::vec3(0.0f);
    float m_speed;
};

#endif
