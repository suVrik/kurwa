#pragma once

#include <string>

class Shader {
    public:
        Shader(const std::string &shader_path, unsigned int shader_type);
        unsigned int get_shader_id() const;
    private:
        void init_shader(const char *shader_code, unsigned int shader_type);
        const std::string load_shader_file(const std::string &shader_path) const;
        void check_shader_compilation_status(unsigned int shader_id) const;
        unsigned int shader_id;
};
