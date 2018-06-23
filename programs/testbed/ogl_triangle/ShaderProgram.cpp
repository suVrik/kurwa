#include <gl.h>
#include <iostream>
#include <vector>
#include <bits/ios_base.h>
#include <fstream>
#include <sstream>
#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader) {
    init_shader_program(vertex_shader, fragment_shader);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_program_id);
}

void ShaderProgram::init_shader_program(const Shader& vertex_shader, const Shader& fragment_shader) {
    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex_shader.get_shader_id());
    glAttachShader(m_program_id, fragment_shader.get_shader_id());
    glLinkProgram(m_program_id);
    check_shader_link_status();
}

void ShaderProgram::use_program() const {
    glUseProgram(m_program_id);
}

int ShaderProgram::get_uniform_id(const std::string &name) const {
    return glGetUniformLocation(m_program_id, name.c_str());
}

void ShaderProgram::check_shader_link_status() const {
    GLint success;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLint log_length;
        glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> log(static_cast<unsigned>(log_length));
        glGetProgramInfoLog(m_program_id, log_length, nullptr, log.data());
        throw std::runtime_error("ERROR: Shader linking failed!\n" + std::string(log.data()) + "\n");
    }
}