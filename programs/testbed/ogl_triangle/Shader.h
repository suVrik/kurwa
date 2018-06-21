#ifndef OPENGL1_SHADER_H
#define OPENGL1_SHADER_H

#include <fstream>
#include <gl.h>
#include <iostream>
#include <sstream>

class Shader {
    public:
        Shader(const GLchar* vertex_path, const GLchar* fragment_path);
        ~Shader() = default;
        void use_program() const;
        unsigned int get_program_id() const;
    private:
        void check_errors(unsigned int id, const std::string &object_type) const;
        unsigned int program_id;
};

#endif //OPENGL1_SHADER_H
