#include <stb_image.h>
#include <gl.h>
#include <iostream>
#include "Texture.h"

Texture::Texture() {
    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture_id);
}

void Texture::set_texture(const std::string &texture_path) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    int width, height, image_channels;
    stbi_uc *data = stbi_load(texture_path.data(), &width, &height, &image_channels, 0);
    if (data != nullptr) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cout << "ERROR: Failed to load texture" << std::endl;
    }
}