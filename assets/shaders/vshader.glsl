#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertex_uv;

out vec2 uv;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    uv = vertex_uv;
}
