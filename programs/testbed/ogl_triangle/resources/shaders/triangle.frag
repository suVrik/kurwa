#version 330 core
in vec3 color;
in vec2 texture_coord;
out vec4 frag_color;
uniform vec4 uni_color;
uniform sampler2D triangle_texture;

void main() {
    frag_color = texture(triangle_texture, texture_coord) * vec4(color, 1.0);
}
