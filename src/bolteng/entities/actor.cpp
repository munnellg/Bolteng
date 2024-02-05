#include "actor.h"

#include "../components/components.h"
#include "../subsystems/subsystems.h"
#include "../logging.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace bolt {
    namespace entities {
        entt::entity create_actor(entt::registry &registry, float x, float y, float z, int tex_id) {
            entt::entity const actor = registry.create();
            float tex_x = (float) (tex_id % 12) / 12.0f;
            float tex_y = (float) (tex_id / 12) / 3.0f;
            float tex_w = 1.0f / 12.0f;
            float tex_h = 1.0f / 3.0f;

            glm::vec3 vertices[4] = {
                glm::vec3(-0.5f, -0.5f, 0.0f),
                glm::vec3( 0.5f, -0.5f, 0.0f),
                glm::vec3( 0.5f,  0.5f, 0.0f),
                glm::vec3(-0.5f,  0.5f, 0.0f)
            };

            int indices[6] = { 0, 1, 2, 2, 3, 0 };

            glm::vec2 const uvs[] = {
                glm::vec2(tex_x,         tex_y + tex_h),
                glm::vec2(tex_x + tex_w, tex_y + tex_h),
                glm::vec2(tex_x + tex_w, tex_y),
                glm::vec2(tex_x,         tex_y),
            };

            RenderComponent rcTile;

            glCreateVertexArrays(1, &rcTile.m_vao);
            glBindVertexArray(rcTile.m_vao);

            glGenBuffers(1, &rcTile.m_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, rcTile.m_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);
            glEnableVertexAttribArray(0);

            glGenBuffers(1, &rcTile.m_ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rcTile.m_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glGenBuffers(1, &rcTile.m_uvs);
            glBindBuffer(GL_ARRAY_BUFFER, rcTile.m_uvs);
            glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);
            glEnableVertexAttribArray(1);

            rcTile.m_nVertices = sizeof(indices);
            registry.emplace<RenderComponent>(actor, std::move(rcTile));

            PositionComponent tcPosition;
            tcPosition.m_position = glm::vec3(x, y, z);
            registry.emplace<PositionComponent>(actor, tcPosition);

            return actor;
        }

        entt::entity create_camera(entt::registry &registry, float x, float y, float w, float h) {
            entt::entity const camera = registry.create();

            float ortho_width  = w;
            float ortho_height = h;
            
            CameraComponent ccCamera;
            ccCamera.m_projection = glm::ortho(
                -ortho_width / 2.0f,  // x1
                ortho_width / 2.0f,   // x2
                -ortho_height / 2.0f, // y1
                ortho_height / 2.0f,  // y2
                0.0f,                 // near view plane
                100.0f                // far view plane
            );

            ccCamera.m_view = glm::lookAt(
                glm::vec3(x, y, 10.0f), // camera is at (4, 3, 3) in world space
                glm::vec3(x, y, 0), // and looks at the origin
                glm::vec3(0, 1, 0)  // head is up (set to 0, -1, 0 to look upside down)
            );
            
            registry.emplace<CameraComponent>(camera, ccCamera);

            return camera;
        }
    }
}
