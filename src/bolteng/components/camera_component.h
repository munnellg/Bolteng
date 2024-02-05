#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include <array>
#include <glm/glm.hpp>

struct CameraComponent {
    glm::mat4 m_projection;
    glm::mat4 m_view;
};

#endif // CAMERA_COMPONENT_H
