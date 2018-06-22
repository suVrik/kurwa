#pragma once

#include <string>

class Texture {
    public:
        explicit Texture();
        ~Texture();
        void set_texture(const std::string &texture_path) const;
    private:
        unsigned int texture_id;

};
