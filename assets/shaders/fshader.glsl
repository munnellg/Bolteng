#version 460 core

// interpolated values from the vertex shader
in vec2 uv;

// output data
out vec4 color;

uniform sampler2D texture_sampler;

void main() {
    color = texture(texture_sampler, uv);
}
