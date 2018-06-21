#include <cmath>
#include <gl.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image/stb_image.h"
#include <vector>

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

    auto version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    std::cout << "Loaded OpenGL "
              << std::to_string(GLAD_VERSION_MAJOR(version)) << "."
              << std::to_string(GLAD_VERSION_MINOR(version)) << std::endl;

    return 0;
}

int load_texture() {
    int width, height, nrChannels;
    auto *data = stbi_load("resources/wall_texture.jpg", &width, &height, &nrChannels, 0);
    if (data != nullptr) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

int main() {
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

    std::vector<GLint> object_indices = {
            0, 1, 3,
            1, 2, 3,
            4, 5, 7,
            5, 6, 7
    };

    std::vector<GLfloat> triangle_data = {
            //vertecis          //colors            //texture coords
            0.0f, -0.9f, 0.0f,  1.0f, 0.0f,  0.0f,  0.0f, 0.0f,
            0.9f, -0.9f, 0.0f,  0.0f, 1.0f,  0.0f,  1.0f, 0.0f,
            0.45f, 0.1f, 0.0f,  0.0f, 0.0f,  1.0f,  0.5f, 1.0f
    };

    GLFWwindow* window;
    auto ret = init_glfw_window(&window);
    if (ret != 0) return ret;

    Shader shader("resources/shaders/statue.vert", "resources/shaders/statue.frag");
    Shader shader2("resources/shaders/triangle.vert", "resources/shaders/triangle.frag");

    GLuint VAOs[2];
    glGenVertexArrays(2, VAOs);

    GLuint VBOs[2];
    glGenBuffers(2, VBOs);

    GLuint EBO;
    glGenBuffers(1, &EBO);

    GLuint texture;
    glGenTextures(1, &texture);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glActiveTexture(GL_TEXTURE0);

    glBufferData(GL_ARRAY_BUFFER, object_vertices.size() * sizeof(GLfloat), &object_vertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, object_indices.size() * sizeof(GLfloat), &object_indices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

    glBufferData(GL_ARRAY_BUFFER, triangle_data.size() * sizeof(GLfloat), &triangle_data.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    load_texture();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLfloat scale_matrix[4][4] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };
    auto scale_location = glGetUniformLocation(shader2.get_program_id(), "scale");
    auto is_polygon_mode_line = false;

    while (glfwWindowShouldClose(window) == 0) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
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

        glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use_program();

        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);

        shader2.use_program();

        auto current_time = glfwGetTime();
        auto some_value = (sin(current_time) / 2.0f) + 0.5f;
        auto vertex_color_location = glGetUniformLocation(shader2.get_program_id(), "uni_color");
        glUniform4f(vertex_color_location, 0.0f, (float) some_value, 0.0f, 1.0f);

        scale_matrix[0][0] = (float) sin(some_value);
        scale_matrix[1][1] = (float) sin(some_value);
        scale_matrix[2][2] = (float) sin(some_value);

        glUniformMatrix4fv(scale_location, 1, GL_TRUE, &scale_matrix[0][0]);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);

    glfwTerminate();
    return 0;
}
