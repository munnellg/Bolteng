#include "render_system.h"
#include <GL/glew.h>
#include <glm/gtx/transform.hpp>
#include "../subsystems/subsystems.h"
#include "../components/camera_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"
#include "../logging.h"
RenderSystem::RenderSystem(entt::registry *pRegistry) : ComponentSystem(pRegistry) {
}

void RenderSystem::update(uint64_t deltaTime) {
    auto view = m_pRegistry->view<RenderComponent, TransformComponent>();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CameraComponent cc = m_pRegistry->get<CameraComponent>(subsystems::render::camera);  
    
    glUseProgram(subsystems::render::shader_program);
    GLuint mvp_loc = glGetUniformLocation(subsystems::render::shader_program, "mvp");

    for (auto [entity, render, transform]: view.each()) {
        glm::mat4 mvp = cc.m_projection * cc.m_view * glm::translate(transform.m_position);
        glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, &mvp[0][0]);
        glBindVertexArray(render.m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, render.m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render.m_ebo);
        glDrawElements(GL_TRIANGLES, render.m_nVertices, GL_UNSIGNED_INT, 0);
    }

    subsystems::display::swap();
}
