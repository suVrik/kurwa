#pragma once

#include <string>
#include "Shader.h"

class ShaderProgram {
    public:
        ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader);
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram &operator=(const ShaderProgram&) = delete;
        ~ShaderProgram();
        void use_program() const;
        int get_uniform_id(const std::string &name) const;
    private:
        void init_shader_program(const Shader& vertex_shader, const Shader& fragment_shader);
        void check_shader_link_status() const;
        unsigned int m_program_id;
};
