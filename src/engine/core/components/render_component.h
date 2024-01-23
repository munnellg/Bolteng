#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <cstdint>

struct RenderComponent {
    uint32_t m_vbo;
    uint32_t m_vao;

    RenderComponent();
};

#endif // RENDERABLE_H
