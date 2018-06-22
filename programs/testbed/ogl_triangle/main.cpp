#include <array>
#include <cmath>
#include <gl.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image/stb_image.h"
#include "Texture.h"
#include "PipelineData.h"
#include "ShaderProgram.h"
#include <vector>
#include <iostream>

int init_glfw_window(GLFWwindow** window) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    std::cout << "Loaded OpenGL "
              << std::to_string(GLAD_VERSION_MAJOR(version)) << "."
              << std::to_string(GLAD_VERSION_MINOR(version)) << std::endl;

    return 0;
}

PipelineData *init_statue_pipeline_data() {
    std::vector<GLfloat> object_vertices = {
            0.5f,  0.1f, 0.0f,   // top right
            0.5f, -0.4f, 0.0f,   // bottom right
            -0.5f, -0.4f, 0.0f,  // bottom left
            -0.5f,  0.1f, 0.0f,  // top left
            0.2f,  0.8f, 0.0f,   // top right
            0.2f, -0.8f, 0.0f,   // bottom right
            -0.2f, -0.8f, 0.0f,  // bottom left
            -0.2f,  0.8f, 0.0f   // top left
    };

    std::vector<GLuint> object_indices = {
            0, 1, 3,
            1, 2, 3,
            4, 5, 7,
            5, 6, 7
    };

    auto *statue_pipeline_data = new PipelineData();
    statue_pipeline_data->initVertexArray();
    statue_pipeline_data->initVertexBuffer(object_vertices);
    statue_pipeline_data->initElementArray(object_indices);
    glBindVertexArray(statue_pipeline_data->get_vertex_array_id());
    glBindBuffer(GL_ARRAY_BUFFER, statue_pipeline_data->get_vertex_buffer_id());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return statue_pipeline_data;
}

PipelineData *init_triangle_pipeline_data() {
    std::vector<GLfloat> triangle_data = {
            //vertecis          //colors            //texture coords
            0.0f, -0.9f, 0.0f,  1.0f, 0.0f,  0.0f,  0.0f, 0.0f,
            0.9f, -0.9f, 0.0f,  0.0f, 1.0f,  0.0f,  1.0f, 0.0f,
            0.45f, 0.1f, 0.0f,  0.0f, 0.0f,  1.0f,  0.5f, 1.0f
    };

    auto *triangle_pipeline_data = new PipelineData();
    triangle_pipeline_data->initVertexArray();
    triangle_pipeline_data->initVertexBuffer(triangle_data);
    glBindVertexArray(triangle_pipeline_data->get_vertex_array_id());
    glBindBuffer(GL_ARRAY_BUFFER, triangle_pipeline_data->get_vertex_buffer_id());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void *>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return triangle_pipeline_data;
}

void handle_glfw_input(GLFWwindow *window, bool &is_polygon_mode_line) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        if (is_polygon_mode_line) {
            is_polygon_mode_line = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            is_polygon_mode_line = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

void main_loop(
        GLFWwindow *window, ShaderProgram *statue_shader, ShaderProgram *triangle_shader,
        PipelineData *statue_pipeline_data, PipelineData *triangle_pipeline_data
) {
    GLfloat scale_matrix[4][4] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    auto is_polygon_mode_line = false;

    while (glfwWindowShouldClose(window) == 0) {
        handle_glfw_input(window, is_polygon_mode_line);

        glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        statue_shader->use_program();
        glBindVertexArray(statue_pipeline_data->get_vertex_array_id());
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        triangle_shader->use_program();
        float some_value = (float) sin(glfwGetTime()) / 2.0f + 0.5f;
        int uniform_color_id = triangle_shader->get_uniform_id("uni_color");
        glUniform4f(uniform_color_id, 0.0f, some_value, 0.0f, 1.0f);

        scale_matrix[0][0] = sinf(some_value);
        scale_matrix[1][1] = sinf(some_value);
        scale_matrix[2][2] = sinf(some_value);

        int uniform_scale_id = triangle_shader->get_uniform_id("scale");
        glUniformMatrix4fv(uniform_scale_id, 1, GL_TRUE, &scale_matrix[0][0]);

        glBindVertexArray(triangle_pipeline_data->get_vertex_array_id());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {
    GLFWwindow* window;
    int ret = init_glfw_window(&window);
    if (ret != 0) {
        glfwTerminate();
        return ret;
    }

    PipelineData *statue_pipeline_data = init_statue_pipeline_data();
    PipelineData *triangle_pipeline_data = init_triangle_pipeline_data();

    auto *statue_vertex_shader = new Shader("resources/shaders/statue.vert", GL_VERTEX_SHADER);
    auto *statue_fragment_shader = new Shader("resources/shaders/statue.frag", GL_FRAGMENT_SHADER);
    auto *statue_shader_program =
            new ShaderProgram(statue_vertex_shader->get_shader_id(), statue_fragment_shader->get_shader_id());
    delete statue_vertex_shader;
    delete statue_fragment_shader;

    auto *triangle_vertex_shader = new Shader("resources/shaders/triangle.vert", GL_VERTEX_SHADER);
    auto *triangle_fragment_shader = new Shader("resources/shaders/triangle.frag", GL_FRAGMENT_SHADER);
    auto *triangle_shader_program =
            new ShaderProgram(triangle_vertex_shader->get_shader_id(), triangle_fragment_shader->get_shader_id());
    delete triangle_vertex_shader;
    delete triangle_fragment_shader;

    auto *triangle_texture = new Texture();
    triangle_texture->set_texture("resources/wall_texture.jpg");

    main_loop(window, statue_shader_program, triangle_shader_program, statue_pipeline_data, triangle_pipeline_data);

    delete triangle_texture;
    delete statue_shader_program;
    delete triangle_shader_program;
    delete statue_pipeline_data;
    delete triangle_pipeline_data;

    glfwTerminate();
    return 0;
}
