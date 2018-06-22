#include <fstream>
#include <gl.h>
#include <iostream>
#include "Shader.h"
#include <sstream>
#include <vector>

Shader::Shader(const std::string &shader_path, unsigned int shader_type) {
    const std::string shader_code = load_shader_file(shader_path);
    const auto *shader_code_char = shader_code.c_str();
    init_shader(shader_code_char, shader_type);
}

void Shader::init_shader(const GLchar *shader_code, const GLenum shader_type) {
    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &shader_code, nullptr);
    glCompileShader(shader_id);
    check_shader_compilation_status(shader_id);
}

const std::string Shader::load_shader_file(const std::string &shader_path) const {
    std::stringstream shader_stream;
    try {
        std::ifstream shader_file;
        shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        shader_file.open(shader_path);

        shader_stream << shader_file.rdbuf();

        shader_file.close();
    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR: Could not read shader file in path: " << shader_path << std::endl << e.what() << std::endl;
    }
    return shader_stream.str();
}

unsigned int Shader::get_shader_id() const {
    return shader_id;
}

void Shader::check_shader_compilation_status(unsigned int shader_id) const {
    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLuint log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, (GLint *) &log_length);
        std::vector<char> log(log_length);
        glGetShaderInfoLog(shader_id, log_length, nullptr, log.data());
        std::cout << "ERROR: shader compilation failed!" << std::endl << log.data() << std::endl;
    }
}
