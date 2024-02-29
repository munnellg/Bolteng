#ifndef RENDER_3D_SCENE_H
#define RENDER_3D_SCENE_H

#include "../bolteng/application/scene.h"
#include "../bolteng/graphics/mesh.h"
#include "../bolteng/graphics/shader.h"
#include "../bolteng/components/camera_component.h"

#include <cstdint>

class Render3DScene : public Scene {
public:
    Render3DScene();

    void onEnter();
    void update(uint64_t);
    void onExit();

private:
    bolt::Mesh m_mesh;
    bolt::Mesh m_triangle;
    bolt::ShaderProgram m_shader;
    CameraComponent m_camera;
};

#endif // RENDER_3D_SCENE_H
