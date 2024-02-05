#ifndef MOVE_COMPONENT
#define MOVE_COMPONENT

#include <glm/glm.hpp>
#include "../logging.h"

struct MoveComponent {
    glm::vec3 m_direction = glm::vec3(0.0f);
    float m_speed;

    int moveUp() {
        m_direction[0] = 0.0f;
        m_direction[1] = 1.0f;
        return 0;
    }

    int moveDown() {
        m_direction[0] =  0.0f;
        m_direction[1] = -1.0f;
        return 0;
    }

    int moveLeft() {
        m_direction[0] = -1.0f;
        m_direction[1] =  0.0f;
        return 0;
    }

    int moveRight() {
        m_direction[0] = 1.0f;
        m_direction[1] = 0.0f;
        return 0;
    }
};

#endif
