#pragma once

#include <string>

class Texture {
    public:
        Texture(const std::string &texture_path, GLuint vertex_array_id);
        ~Texture();
        void bind_texture() const;
        void unbind_texture() const;
    private:
        unsigned int m_texture_id;
};
