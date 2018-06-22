#pragma once

#include <string>
#include "Shader.h"

class ShaderProgram {
    public:
        ShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id);
        ~ShaderProgram();
        void use_program() const;
        int get_uniform_id(const std::string &name) const;
    private:
        void init_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id);
        void check_shader_link_status() const;
        unsigned int program_id;
};
