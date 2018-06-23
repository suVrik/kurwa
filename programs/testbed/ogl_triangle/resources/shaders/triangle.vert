#version 330 core
layout (location = 0) in vec3 position;
layout(location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_texture_coord;
out vec3 color;
out vec2 texture_coord;
uniform mat4 scale;

void main() {
    texture_coord = in_texture_coord;
    color = in_color;
    gl_Position = scale * vec4(position, 1.0);
}
