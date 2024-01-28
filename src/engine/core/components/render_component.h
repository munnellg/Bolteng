#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <cstdint>
#include <GL/glew.h>
#include <utility>

struct RenderComponent {
    uint32_t m_vbo;
    uint32_t m_vao;
    uint32_t m_ebo;
    uint32_t m_uvs;
    uint32_t m_nVertices;
    
    RenderComponent()
        : m_vbo(0),
        m_vao(0),
        m_ebo(0),
        m_uvs(0),
        m_nVertices(0)
    {}

    RenderComponent(RenderComponent const &rc)
        : m_vbo(rc.m_vbo),
        m_vao(rc.m_vao),
        m_ebo(rc.m_ebo),
        m_uvs(rc.m_uvs),
        m_nVertices(rc.m_nVertices)
    {
    }

    RenderComponent(RenderComponent &&rc)
        : m_vbo(std::exchange(rc.m_vbo, 0)),
        m_vao(std::exchange(rc.m_vao, 0)),
        m_ebo(std::exchange(rc.m_ebo, 0)),
        m_uvs(std::exchange(rc.m_uvs, 0)),
        m_nVertices(std::exchange(rc.m_nVertices, 0))
    {}
    
    RenderComponent& operator=(RenderComponent const &rc) {
        m_vbo = rc.m_vbo;
        m_vao = rc.m_vao;
        m_ebo = rc.m_ebo;
        m_uvs = rc.m_uvs;
        m_nVertices = rc.m_nVertices;
        return *this;
    }
 
    RenderComponent& operator=(RenderComponent&& rc) noexcept {
        m_vbo = std::exchange(rc.m_vbo, 0);
        m_vao = std::exchange(rc.m_vao, 0);
        m_ebo = std::exchange(rc.m_ebo, 0);
        m_uvs = std::exchange(rc.m_uvs, 0);
        m_nVertices = std::exchange(rc.m_nVertices, 0);
        return *this;
    }

    ~RenderComponent() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
        glDeleteBuffers(1, &m_uvs);
    }
};

#endif // RENDERABLE_H
