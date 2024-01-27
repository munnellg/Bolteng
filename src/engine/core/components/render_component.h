#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <cstdint>

struct RenderComponent {
    uint32_t m_vbo;
    uint32_t m_vao;
    uint32_t m_ebo;
    uint32_t m_uvs;
    uint32_t m_nVertices;
};

#endif // RENDERABLE_H
