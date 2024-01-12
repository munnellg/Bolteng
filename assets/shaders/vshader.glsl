#version 460 core

in vec3 position;

void main() {
    gl_position = vec4(position, 1.0);
}
