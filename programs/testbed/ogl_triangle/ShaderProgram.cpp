#include <gl.h>
#include <iostream>
#include <vector>
#include <bits/ios_base.h>
#include <fstream>
#include <sstream>
#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id) {
    init_shader_program(vertex_shader_id, fragment_shader_id);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program_id);
}

void ShaderProgram::init_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id) {
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    check_shader_link_status();

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

void ShaderProgram::use_program() const {
    glUseProgram(program_id);
}

int ShaderProgram::get_uniform_id(const std::string &name) const {
    return glGetUniformLocation(program_id, name.data());
}

void ShaderProgram::check_shader_link_status() const {
    GLint success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLuint log_length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, (GLint *) &log_length);
        std::vector<char> log(log_length);
        glGetProgramInfoLog(program_id, log_length, nullptr, log.data());
        throw std::runtime_error("ERROR: Shader linking failed!\n" + std::string(log.data()) + "\n");
    }
}