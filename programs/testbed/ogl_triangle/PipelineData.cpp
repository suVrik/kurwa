#include <gl.h>
#include <cassert>
#include "PipelineData.h"

PipelineData::PipelineData() : m_vertex_array_id(0), m_vertex_buffer_id(0), m_element_buffer_id(0) {}

PipelineData::PipelineData(PipelineData&& that) noexcept {
    m_vertex_array_id = that.m_vertex_array_id;
    m_vertex_buffer_id = that.m_vertex_buffer_id;
    m_element_buffer_id = that.m_element_buffer_id;
    that.m_vertex_array_id = 0;
    that.m_vertex_buffer_id = 0;
    that.m_element_buffer_id = 0;
}

PipelineData::~PipelineData() {
    glDeleteVertexArrays(1, &m_vertex_array_id);
    glDeleteBuffers(1, &m_vertex_buffer_id);
    glDeleteBuffers(1, &m_element_buffer_id);
}

void PipelineData::initVertexArray() {
    assert(m_vertex_array_id == 0 && "Vertex array must be initialized only once!");
    glGenVertexArrays(1, &m_vertex_array_id);
}

void PipelineData::initVertexBuffer(std::vector<GLfloat> data) {
    assert(m_vertex_buffer_id == 0 && "Vertex buffer must be initialized only once!");
    glGenBuffers(1, &m_vertex_buffer_id);

    glBindVertexArray(m_vertex_array_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void PipelineData::initElementArray(std::vector<GLuint> data) {
    assert(m_element_buffer_id == 0 && "Element array must be initialized only once!");
    glGenBuffers(1, &m_element_buffer_id);

    glBindVertexArray(m_vertex_array_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data.front(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

const unsigned int PipelineData::get_vertex_array_id() const {
    return m_vertex_array_id;
}
const unsigned int PipelineData::get_vertex_buffer_id() const {
    return m_vertex_buffer_id;
}
