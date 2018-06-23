#include <stb_image.h>
#include <gl.h>
#include <iostream>
#include "Texture.h"

Texture::Texture(const std::string& texture_path, GLuint vertex_array_id) {
    glGenTextures(1, &m_texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vertex_array_id);
    bind_texture();
    int width, height, image_channels;
    stbi_uc* data = stbi_load(texture_path.c_str(), &width, &height, &image_channels, 0);
    if (data != nullptr) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cout << "ERROR: Failed to load texture" << std::endl;
    }
    unbind_texture();
    glBindVertexArray(0);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture_id);
}

void Texture::bind_texture() const {
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::unbind_texture() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
