#include "Shader.h"

Shader::Shader(const char *vertex_path, const char *fragment_path) {
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;

    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertex_shader_file.open(vertex_path);
        fragment_shader_file.open(fragment_path);
        std::stringstream vertex_shader_stream, fragment_shader_stream;

        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();

        vertex_shader_file.close();
        fragment_shader_file.close();

        vertex_code = vertex_shader_stream.str();
        fragment_code = fragment_shader_stream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ, " << e.what() << std::endl;
    }

    const auto *vertex_shader_code = vertex_code.c_str();
    const auto *fragment_shader_code = fragment_code.c_str();

    unsigned int vertex_id, fragment_id;

    vertex_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_id, 1, &vertex_shader_code, nullptr);
    glCompileShader(vertex_id);
    check_errors(vertex_id, "VERTEX");

    fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_id, 1, &fragment_shader_code, nullptr);
    glCompileShader(fragment_id);
    check_errors(fragment_id, "FRAGMENT");

    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);
    check_errors(program_id, "SHADER");

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

void Shader::use_program() const {
    glUseProgram(program_id);
}

unsigned int Shader::get_program_id() const {
    return program_id;
}

void Shader::check_errors(unsigned int id, const std::string &object_type) const {
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (success == 0) {
        char info_log[512];
        glGetProgramInfoLog(id, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::" << object_type << "::LINKING_FAILED\n" << info_log << std::endl;
    }
}


