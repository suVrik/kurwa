#include <gl.h>
#include "PipelineData.h"

PipelineData::PipelineData() : vertex_array_id(0), vertex_buffer_id(0), element_buffer_id(0) {}

PipelineData::~PipelineData() {
    glDeleteVertexArrays(1, &vertex_array_id);
    glDeleteBuffers(1, &vertex_buffer_id);
}

void PipelineData::initVertexArray() {
    glGenVertexArrays(1, &vertex_array_id);
}

void PipelineData::initVertexBuffer(std::vector<GLfloat> data) {
    glGenBuffers(1, &vertex_buffer_id);

    glBindVertexArray(vertex_array_id);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void PipelineData::initElementArray(std::vector<GLuint> data) {
    glGenBuffers(1, &element_buffer_id);

    glBindVertexArray(vertex_array_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data.front(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

const unsigned int PipelineData::get_vertex_array_id() const {
    return vertex_array_id;
}
const unsigned int PipelineData::get_vertex_buffer_id() const {
    return vertex_buffer_id;
}
