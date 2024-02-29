#include "render_3d_scene.h"
#include "../bolteng/bolteng.h"

#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

float theta        = 0.0f;
float radius       = 100.0f;
float rads_per_sec = 3.0f;

Render3DScene::Render3DScene() {
}

void Render3DScene::onEnter() {

    std::optional<bolt::ShaderProgram> shader = bolt::ShaderProgram::build("assets/shaders/basic_vshader.glsl", "assets/shaders/basic_fshader.glsl");

    if (shader) {
        m_shader = std::move(*shader);
        m_shader.enable();

    }

    // std::optional<bolt::Mesh> mesh = bolt::assimp_load("assets/meshes/kenny/detail_treeLarge.glb");
    // std::optional<bolt::Mesh> mesh = bolt::assimp_load("assets/meshes/table/table.obj");
    // std::optional<bolt::Mesh> mesh = bolt::assimp_load("assets/meshes/backpack/backpack.obj");
    std::optional<bolt::Mesh> mesh = bolt::assimp_load("assets/meshes/treasury/treasury.obj");
    if (mesh) {
        m_mesh = std::move(*mesh);
        m_mesh.setup();
    }
}

void Render3DScene::update(uint64_t deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    theta += (rads_per_sec * deltaTime) / 1000.0f;

    m_camera.m_projection = glm::perspective(glm::radians(45.0f), bolt::subsystems::display::aspect, 0.1f, 200.0f);

    float x = radius * cos(theta);
    float z = radius * sin(theta);

    m_camera.m_view = glm::lookAt(
        glm::vec3(x, 2.25, z), // camera is at (4, 3, 3) in world space
        glm::vec3(0, 2.25, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // head is up (set to 0, -1, 0 to look upside down)
    );

    glm::mat4 mvp = m_camera.m_projection * m_camera.m_view;
    glUniformMatrix4fv(m_shader.getUniform("mvp"), 1, GL_FALSE, &mvp[0][0]);

    m_mesh.draw();

    bolt::subsystems::display::swap();
}

void Render3DScene::onExit() {

}

